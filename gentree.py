#!/usr/bin/env python
#
# Generate the output tree, by default in the output/ directory
# but a different one may be specified. The directory must be
# empty already. It's also allowed to not exist.
#

import argparse, sys, os, errno, shutil, re

def read_copy_list(kerneldir, copyfile):
    ret = []
    for item in copyfile:
        # remove leading/trailing whitespace
        item = item.strip()
        # comments
        if not item or item[0] == '#':
            continue
        if item[0] == '/':
            raise Exception("Input path '%s' is absolute path, this isn't allowed" % (item, ))
        # check for expected input
        src = os.path.join(kerneldir, item)
        if item[-1] == '/':
            if not os.path.isdir(src):
                raise Exception("Input path '%s' isn't a directory in '%s'" % (item, kerneldir))
        else:
            if not os.path.isfile(src):
                raise Exception("Input path '%s' isn't a file in '%s'" % (item, kerneldir))
        ret.append((kerneldir, item))
    return ret

def check_output_dir(d, clean):
    if clean:
        shutil.rmtree(d, ignore_errors=True)
    try:
        os.rmdir(d)
    except OSError, e:
        if e.errno != errno.ENOENT:
            raise

def copy_files(copy_list, outdir):
    for src, tgt in copy_list:
        if tgt == '':
            shutil.copytree(src, outdir, ignore=shutil.ignore_patterns('*~'))
        elif tgt[-1] == '/':
            def copy_ignore(dir, entries):
                r = []
                for i in entries:
                    if (not i[-1] in ('c', 'h') and
                        i[-4:] != '.awk' and
                        not i in ('Kconfig', 'Makefile') and
                        not os.path.isdir(os.path.join(dir, i))):
                        r.append(i)
                return r
            shutil.copytree(os.path.join(src, tgt),
                            os.path.join(outdir, tgt),
                            ignore=copy_ignore)
        else:
            try:
                os.makedirs(os.path.join(outdir, os.path.dirname(tgt)))
            except OSError, e:
                # ignore dirs we might have created just now
                if e.errno != errno.EEXIST:
                    raise
            shutil.copy(os.path.join(src, tgt),
                        os.path.join(outdir, tgt))

def main():
    # set up and parse arguments
    parser = argparse.ArgumentParser(description='generate backport tree')
    parser.add_argument('kerneldir', metavar='<kernel tree>', type=str,
                        help='Kernel tree to copy drivers from')
    parser.add_argument('outdir', metavar='<output directory>', type=str,
                        help='Directory to write the generated tree to')
    parser.add_argument('--copy-list', metavar='<listfile>', type=argparse.FileType('r'),
                        default='copy-list',
                        help='File containing list of files/directories to copy, default "copy-list"')
    parser.add_argument('--clean', const=True, default=False, action="store_const",
                        help='Clean output directory instead of erroring if it isn\'t empty')
    parser.add_argument('--base-name', metavar='<name>', type=str, default='Linux',
                        help='name of base tree, default just "Linux"')
    args = parser.parse_args()

    # find self
    source_dir = os.path.abspath(os.path.dirname(sys.argv[0]))

    # first thing to copy is our own plumbing -- we start from that
    copy_list = [(os.path.join(source_dir, 'plumbing'), '')]
    # then add stuff from the copy list file
    copy_list.extend(read_copy_list(args.kerneldir, args.copy_list))
    # add compat to the list
    copy_list.append((os.path.join(source_dir, 'compat'), 'compat/'))
    copy_list.append((os.path.join(source_dir, 'compat'), 'include/'))

    # validate output directory
    check_output_dir(args.outdir, args.clean)

    # do the copy
    copy_files(copy_list, args.outdir)

    # some post-processing is required
    sys.path.append(os.path.join(source_dir, 'lib'))
    import kconfig

    configtree = kconfig.ConfigTree(os.path.join(args.outdir, 'Kconfig'))
    configtree.prune_sources(ignore=['Kconfig.kernel', 'Kconfig.versions'])
    configtree.force_tristate_modular()
    configtree.modify_selects()

    # write the versioning file
    import git
    backports_version = git.describe(tree=source_dir)
    kernel_version = git.describe(tree=args.kerneldir)
    f = open(os.path.join(args.outdir, 'versions'), 'w')
    f.write('BACKPORTS_VERSION="%s"\n' % backports_version)
    f.write('KERNEL_VERSION="%s"\n' % kernel_version)
    f.write('KERNEL_NAME="%s"\n' % args.base_name)
    f.close()

    symbols = configtree.symbols()

    # write local symbol list
    f = open(os.path.join(args.outdir, '.local-symbols'), 'w')
    for sym in symbols:
        f.write('%s=\n' % sym)
    f.close()

    # XXX Apply patches here!!

    # rewrite Makefile and source symbols
    r = 'CONFIG_((' + '|'.join(symbols) + ')([^A-Za-z0-9_]|$))'
    r = re.compile(r, re.MULTILINE)
    for root, dirs, files in os.walk(args.outdir):
        for f in files:
            data = open(os.path.join(root, f), 'r').read()
            data = r.sub(r'CPTCFG_\1', data)
            fo = open(os.path.join(root, f), 'w')
            fo.write(data)
            fo.close()

main()

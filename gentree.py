#!/usr/bin/env python
#
# Generate the output tree, by default in the output/ directory
# but a different one may be specified. The directory must be
# empty already. It's also allowed to not exist.
#

import argparse, sys, os, errno, shutil, re, subprocess

# find self
source_dir = os.path.abspath(os.path.dirname(sys.argv[0]))
sys.path.append(os.path.join(source_dir, 'lib'))
import kconfig, git, patch, make

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
        if ' -> ' in item:
            srcitem, dstitem = item.split(' -> ')
            if (srcitem[-1] == '/') != (dstitem[-1] == '/'):
                raise Exception("Cannot copy file/dir to dir/file")
        else:
            srcitem = dstitem = item
        # check for expected input
        src = os.path.join(kerneldir, srcitem)
        if item[-1] == '/':
            if not os.path.isdir(src):
                raise Exception("Input path '%s' isn't a directory in '%s'" % (srcitem, kerneldir))
        else:
            if not os.path.isfile(src):
                raise Exception("Input path '%s' isn't a file in '%s'" % (srcitem, kerneldir))
        ret.append((kerneldir, srcitem, dstitem))
    return ret

def check_output_dir(d, clean):
    if clean:
        shutil.rmtree(d, ignore_errors=True)
    try:
        os.rmdir(d)
    except OSError, e:
        if e.errno != errno.ENOENT:
            raise

def copytree(src, dst, symlinks=False, ignore=None):
    names = os.listdir(src)
    if ignore is not None:
        ignored_names = ignore(src, names)
    else:
        ignored_names = set()

    if not os.path.isdir(dst):
        os.makedirs(dst)
    errors = []
    for name in names:
        if name in ignored_names:
            continue
        srcname = os.path.join(src, name)
        dstname = os.path.join(dst, name)
        try:
            if symlinks and os.path.islink(srcname):
                linkto = os.readlink(srcname)
                os.symlink(linkto, dstname)
            elif os.path.isdir(srcname):
                copytree(srcname, dstname, symlinks, ignore)
            else:
                shutil.copy2(srcname, dstname)
        except (IOError, os.error) as why:
            errors.append((srcname, dstname, str(why)))
        # catch the Error from the recursive copytree so that we can
        # continue with other files
        except shutil.Error as err:
            errors.extend(err.args[0])
    try:
        shutil.copystat(src, dst)
    except WindowsError:
        # can't copy file access times on Windows
        pass
    except OSError as why:
        errors.extend((src, dst, str(why)))
    if errors:
        raise shutil.Error(errors)

def copy_files(copy_list, outdir):
    for srcpath, srcitem, tgtitem in copy_list:
        if tgtitem == '':
            copytree(srcpath, outdir, ignore=shutil.ignore_patterns('*~'))
        elif tgtitem[-1] == '/':
            def copy_ignore(dir, entries):
                r = []
                for i in entries:
                    if (not i[-1] in ('c', 'h') and
                        i[-4:] != '.awk' and
                        not i in ('Kconfig', 'Makefile') and
                        not os.path.isdir(os.path.join(dir, i))):
                        r.append(i)
                return r
            copytree(os.path.join(srcpath, srcitem),
                     os.path.join(outdir, tgtitem),
                     ignore=copy_ignore)
        else:
            try:
                os.makedirs(os.path.join(outdir, os.path.dirname(tgtitem)))
            except OSError, e:
                # ignore dirs we might have created just now
                if e.errno != errno.EEXIST:
                    raise
            shutil.copy(os.path.join(srcpath, srcitem),
                        os.path.join(outdir, tgtitem))

def git_debug_init(args):
    if not args.gitdebug:
        return
    git.init(tree=args.outdir)
    git.commit_all("Copied code", tree=args.outdir)

def git_debug_snapshot(args, name):
    if not args.gitdebug:
        return
    git.commit_all(name, tree=args.outdir)

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
    parser.add_argument('--refresh', const=True, default=False, action="store_const",
                        help='Refresh patches as they are applied, the source dir will be modified!')
    parser.add_argument('--base-name', metavar='<name>', type=str, default='Linux',
                        help='name of base tree, default just "Linux"')
    parser.add_argument('--gitdebug', const=True, default=False, action="store_const",
                        help='Use git, in the output tree, to debug the various transformation steps ' +
                             'that the tree generation makes (apply patches, ...)')
    args = parser.parse_args()

    # first thing to copy is our own plumbing -- we start from that
    copy_list = [(os.path.join(source_dir, 'plumbing'), '', '')]
    # then add stuff from the copy list file
    copy_list.extend(read_copy_list(args.kerneldir, args.copy_list))
    # add compat to the list
    copy_list.append((os.path.join(source_dir, 'compat'), 'compat/', 'compat/'))
    copy_list.append((os.path.join(source_dir, 'compat'), 'include/', 'include/'))

    # validate output directory
    check_output_dir(args.outdir, args.clean)

    # do the copy
    copy_files(copy_list, args.outdir)

    git_debug_init(args)

    # some post-processing is required
    configtree = kconfig.ConfigTree(os.path.join(args.outdir, 'Kconfig'))
    configtree.prune_sources(ignore=['Kconfig.kernel', 'Kconfig.versions'])
    git_debug_snapshot(args, "prune Kconfig tree")
    configtree.force_tristate_modular()
    git_debug_snapshot(args, "force tristate options modular")
    configtree.modify_selects()
    git_debug_snapshot(args, "convert select to depends on")

    # write the versioning file
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

    git_debug_snapshot(args, "add versions/symbols files")

    patchdirs = []
    for root, dirs, files in os.walk(os.path.join(source_dir, 'patches')):
        if not dirs:
            patchdirs.append(root)
    patchdirs.sort()
    for pdir in patchdirs:
        l = os.listdir(pdir)
        printed = False
        for pfile in l:
            pfile = os.path.join(pdir, pfile)
            p = patch.fromfile(pfile)
            if not p:
                continue
            patched_file = '/'.join(p.items[0].source.split('/')[1:])
            fullfn = os.path.join(args.outdir, patched_file)
            if not os.path.exists(fullfn):
                continue
            if not printed:
                print "Applying changes from", os.path.basename(pdir)
                printed = True
            if args.refresh:
                shutil.copyfile(fullfn, fullfn + '.orig_file')
            process = subprocess.Popen(['patch', '-p1'], stdout=subprocess.PIPE,
                                       stderr=subprocess.STDOUT, stdin=subprocess.PIPE,
                                       close_fds=True, universal_newlines=True,
                                       cwd=args.outdir)
            output = process.communicate(input=open(pfile, 'r').read())[0]
            output = output.split('\n')
            if output[-1] == '':
                output = output[:-1]
            for line in output:
                print '>', line
            if process.returncode != 0:
                print "Patch failed!"
                sys.exit(2)
            if args.refresh:
                process = subprocess.Popen(['diff', '-u', patched_file + '.orig_file', patched_file,
                                            '--label', 'a/' + patched_file,
                                            '--label', 'b/' + patched_file],
                                           stdout=subprocess.PIPE, close_fds=True,
                                           universal_newlines=True, cwd=args.outdir)
                diff = process.communicate()[0]
                if not process.returncode in (0, 1):
                    print "Diffing for refresh failed!"
                    sys.exit(3)
                pfilef = open(pfile, 'w')
                pfilef.write(diff)
                pfilef.close()
                os.unlink(fullfn + '.orig_file')
        # remove orig/rej files that patch sometimes creates
        for root, dirs, files in os.walk(args.outdir):
            for f in files:
                if f[-5:] == '.orig' or f[-4:] == '.rej':
                    os.unlink(os.path.join(root, f))
        if not printed:
            print "Not applying changes from %s, not needed" % (os.path.basename(pdir),)
        else:
            git_debug_snapshot(args, "apply backport patches from %s" % (os.path.basename(pdir),))


    # rewrite Makefile and source symbols
    regexes = []
    for some_symbols in [symbols[i:i + 50] for i in range(0, len(symbols), 50)]:
        r = 'CONFIG_((' + '|'.join([s + '(_MODULE)?' for s in some_symbols]) + ')([^A-Za-z0-9_]|$))'
        regexes.append(re.compile(r, re.MULTILINE))
    for root, dirs, files in os.walk(args.outdir):
        # don't go into .git dir (possible debug thing)
        if '.git' in dirs:
            dirs.remove('.git')
        for f in files:
            data = open(os.path.join(root, f), 'r').read()
            for r in regexes:
                data = r.sub(r'CPTCFG_\1', data)
            fo = open(os.path.join(root, f), 'w')
            fo.write(data)
            fo.close()

    git_debug_snapshot(args, "rename config symbol usage")

    # disable unbuildable Kconfig symbols and stuff Makefiles that doesn't exist
    maketree = make.MakeTree(os.path.join(args.outdir, 'Makefile.kernel'))
    disable_kconfig = []
    disable_makefile = []
    for sym in maketree.get_impossible_symbols():
        if sym[:7] == 'CPTCFG_':
            disable_kconfig.append(sym[7:])
        else:
            disable_makefile.append(sym[7:])

    configtree.disable_symbols(disable_kconfig)
    git_debug_snapshot(args, "disable impossible kconfig symbols")

    regexes = []
    for some_symbols in [disable_makefile[i:i + 50] for i in range(0, len(disable_makefile), 50)]:
        r = '(CONFIG_(' + '|'.join([s for s in some_symbols]) + '))'
        regexes.append(re.compile(r, re.MULTILINE))
    for f in maketree.get_makefiles():
        data = open(f, 'r').read()
        for r in regexes:
            data = r.sub(r'IMPOSSIBLE_\2', data)
        fo = open(f, 'w')
        fo.write(data)
        fo.close()
    git_debug_snapshot(args, "disable unsatisfied Makefile parts")

main()

#!/usr/bin/env python
#
# Generate the output tree into a specified directory.
#

import argparse, sys, os, errno, shutil, re, subprocess

# find self
source_dir = os.path.abspath(os.path.dirname(__file__))
sys.path.append(source_dir)
# and import libraries we have
from lib import kconfig, git, patch, make


def read_copy_list(copyfile):
    """
    Read a copy-list file and return a list of (source, target)
    tuples. The source and target are usually the same, but in
    the copy-list file there may be a rename included.
    """
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
        ret.append((srcitem, dstitem))
    return ret


def read_dependencies(depfilename):
    """
    Read a (the) dependency file and return the list of
    dependencies as a dictionary, mapping a Kconfig symbol
    to a list of kernel version dependencies. While reading
    ignore blank/commented lines.
    """
    ret = {}
    depfile = open(depfilename, 'r')
    for item in depfile:
        item = item.strip()
        if not item or item[0] == '#':
            continue
        sym, dep = item.split()
        if not sym in ret:
            ret[sym] = [dep, ]
        else:
            ret[sym].append(dep)
    return ret


def check_output_dir(d, clean):
    """
    Check that the output directory doesn't exist or is empty,
    unless clean is True in which case it's nuked. This helps
    sanity check the output when generating a tree, so usually
    running with --clean isn't suggested.
    """
    if clean:
        shutil.rmtree(d, ignore_errors=True)
    try:
        os.rmdir(d)
    except OSError, e:
        if e.errno != errno.ENOENT:
            raise


def copytree(src, dst, symlinks=False, ignore=None):
    """
    Copy a directory tree. This differs from shutil.copytree()
    in that it allows destination directories to already exist.
    """
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


def copy_files(srcpath, copy_list, outdir):
    """
    Copy the copy_list files and directories from the srcpath
    to the outdir. The copy_list contains source and target
    names.

    For now, it also ignores any *~ editor backup files, though
    this should probably be generalized (maybe using .gitignore?)
    Similarly the code that only copies some files (*.c, *.h,
    *.awk, Kconfig, Makefile) to avoid any build remnants in the
    kernel if they should exist.
    """
    for srcitem, tgtitem in copy_list:
        if tgtitem == '':
            copytree(srcpath, outdir, ignore=shutil.ignore_patterns('*~'))
        elif tgtitem[-1] == '/':
            def copy_ignore(dir, entries):
                r = []
                for i in entries:
                    if i[-1] in ('o', '~'):
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


def copy_git_files(srcpath, copy_list, rev, outdir):
    """
    "Copy" files from a git repository. This really means listing them with
    ls-tree and then using git show to obtain all the blobs.
    """
    for srcitem, tgtitem in copy_list:
        for m, t, h, f in git.ls_tree(rev=rev, files=(srcitem,), tree=srcpath):
            assert t == 'blob'
            f = os.path.join(outdir, f)
            d = os.path.dirname(f)
            if not os.path.exists(d):
                os.makedirs(d)
            outf = open(f, 'w')
            git.get_blob(h, outf, tree=srcpath)
            outf.close()
            os.chmod(f, int(m, 8))


def git_debug_init(args):
    """
    Initialize a git repository in the output directory and commit the current
    code in it. This is only used for debugging the transformations this code
    will do to the output later.
    """
    if not args.gitdebug:
        return
    git.init(tree=args.outdir)
    git.commit_all("Copied code", tree=args.outdir)


def git_debug_snapshot(args, name):
    """
    Take a git snapshot for the debugging.
    """
    if not args.gitdebug:
        return
    git.commit_all(name, tree=args.outdir)


def _main():
    # set up and parse arguments
    parser = argparse.ArgumentParser(description='generate backport tree')
    parser.add_argument('kerneldir', metavar='<kernel tree>', type=str,
                        help='Kernel tree to copy drivers from')
    parser.add_argument('outdir', metavar='<output directory>', type=str,
                        help='Directory to write the generated tree to')
    parser.add_argument('--copy-list', metavar='<listfile>', type=argparse.FileType('r'),
                        default='copy-list',
                        help='File containing list of files/directories to copy, default "copy-list"')
    parser.add_argument('--git-revision', metavar='<revision>', type=str,
                        help='git commit revision (see gitrevisions(7)) to take objects from.' +
                             'If this is specified, the kernel tree is used as git object storage ' +
                             'and we use git ls-tree to get the files.')
    parser.add_argument('--clean', const=True, default=False, action="store_const",
                        help='Clean output directory instead of erroring if it isn\'t empty')
    parser.add_argument('--refresh', const=True, default=False, action="store_const",
                        help='Refresh patches as they are applied, the source dir will be modified!')
    parser.add_argument('--base-name', metavar='<name>', type=str, default='Linux',
                        help='name of base tree, default just "Linux"')
    parser.add_argument('--gitdebug', const=True, default=False, action="store_const",
                        help='Use git, in the output tree, to debug the various transformation steps ' +
                             'that the tree generation makes (apply patches, ...)')
    parser.add_argument('--verbose', const=True, default=False, action="store_const",
                        help='Print more verbose information')
    parser.add_argument('--extra-driver', nargs=2, metavar=('<source dir>', '<copy-list>'), type=str,
                        action='append', default=[], help='Extra driver directory/copy-list.')
    args = parser.parse_args()

    def logwrite(msg):
        sys.stdout.write(msg)
        sys.stdout.write('\n')
        sys.stdout.flush()

    return process(args.kerneldir, args.outdir, args.copy_list,
                   git_revision=args.git_revision, clean=args.clean,
                   refresh=args.refresh, base_name=args.base_name,
                   gitdebug=args.gitdebug, verbose=args.verbose,
                   extra_driver=args.extra_driver, logwrite=logwrite)

def process(kerneldir, outdir, copy_list_file, git_revision=None,
            clean=False, refresh=False, base_name="Linux", gitdebug=False,
            verbose=False, extra_driver=[], logwrite=lambda x:None):
    class Args(object):
        def __init__(self, kerneldir, outdir, copy_list_file,
                     git_revision, clean, refresh, base_name,
                     gitdebug, verbose, extra_driver):
            self.kerneldir = kerneldir
            self.outdir = outdir
            self.copy_list = copy_list_file
            self.git_revision = git_revision
            self.clean = clean
            self.refresh = refresh
            self.base_name = base_name
            self.gitdebug = gitdebug
            self.verbose = verbose
            self.extra_driver = extra_driver
    args = Args(kerneldir, outdir, copy_list_file,
                git_revision, clean, refresh, base_name,
                gitdebug, verbose, extra_driver)
    # start processing ...

    copy_list = read_copy_list(args.copy_list)
    deplist = read_dependencies(os.path.join(source_dir, 'dependencies'))

    # validate output directory
    check_output_dir(args.outdir, args.clean)

    # do the copy
    backport_files = [(x, x) for x in [
        'Kconfig', 'Makefile', 'Makefile.build', 'Makefile.kernel', '.gitignore',
        'Makefile.real', 'compat/', 'include/', 'kconfig/', 'defconfigs/',
    ]]
    if not args.git_revision:
        logwrite('Copy original source files ...')
        copy_files(os.path.join(source_dir, 'backport'), backport_files, args.outdir)
        copy_files(args.kerneldir, copy_list, args.outdir)
    else:
        logwrite('Get original source files from git ...')
        copy_files(os.path.join(source_dir, 'backport'), backport_files, args.outdir)
        copy_git_files(args.kerneldir, copy_list, args.git_revision, args.outdir)

    # FIXME: should we add a git version of this (e.g. --git-extra-driver)?
    for src, copy_list in args.extra_driver:
        copy_files(src, read_copy_list(open(copy_list, 'r')), args.outdir)

    git_debug_init(args)

    logwrite('Apply patches ...')
    patchdirs = []
    for root, dirs, files in os.walk(os.path.join(source_dir, 'patches')):
        if not dirs:
            patchdirs.append(root)
    patchdirs.sort()
    for pdir in patchdirs:
        l = os.listdir(pdir)
        printed = False
        for pfile in l:
            # FIXME: again, use .gitignore?
            if pfile[-1] == '~':
                continue
            pfile = os.path.join(pdir, pfile)
            # read the patch file
            p = patch.fromfile(pfile)
            # if it is one ...
            if not p:
                continue
            # check if the first file the patch touches exists, if so
            # assume the patch needs to be applied -- otherwise continue
            patched_file = '/'.join(p.items[0].source.split('/')[1:])
            fullfn = os.path.join(args.outdir, patched_file)
            if not os.path.exists(fullfn):
                continue
            if not printed:
                if args.verbose:
                    logwrite("Applying changes from %s" % os.path.basename(pdir))
                printed = True
            if args.refresh:
                # but for refresh, of course look at all files the patch touches
                for patchitem in p.items:
                    patched_file = '/'.join(patchitem.source.split('/')[1:])
                    fullfn = os.path.join(args.outdir, patched_file)
                    shutil.copyfile(fullfn, fullfn + '.orig_file')

            process = subprocess.Popen(['patch', '-p1'], stdout=subprocess.PIPE,
                                       stderr=subprocess.STDOUT, stdin=subprocess.PIPE,
                                       close_fds=True, universal_newlines=True,
                                       cwd=args.outdir)
            output = process.communicate(input=open(pfile, 'r').read())[0]
            output = output.split('\n')
            if output[-1] == '':
                output = output[:-1]
            if args.verbose:
                for line in output:
                    logwrite('> %s' % line)
            if process.returncode != 0:
                if not args.verbose:
                    logwrite("Failed to apply changes from %s" % os.path.basename(pdir))
                    for line in output:
                        logwrite('> %s' % line)
                return 2

            if args.refresh:
                pfilef = open(pfile + '.tmp', 'w')
                for patchitem in p.items:
                    patched_file = '/'.join(patchitem.source.split('/')[1:])
                    fullfn = os.path.join(args.outdir, patched_file)
                    process = subprocess.Popen(['diff', '-u', patched_file + '.orig_file', patched_file,
                                                '--label', 'a/' + patched_file,
                                                '--label', 'b/' + patched_file],
                                               stdout=pfilef, close_fds=True,
                                               universal_newlines=True, cwd=args.outdir)
                    process.wait()
                    os.unlink(fullfn + '.orig_file')
                    if not process.returncode in (0, 1):
                        logwrite("Diffing for refresh failed!")
                        pfilef.close()
                        os.unlink(pfile + '.tmp')
                        return 3
                pfilef.close()
                os.rename(pfile + '.tmp', pfile)

        # remove orig/rej files that patch sometimes creates
        for root, dirs, files in os.walk(args.outdir):
            for f in files:
                if f[-5:] == '.orig' or f[-4:] == '.rej':
                    os.unlink(os.path.join(root, f))
        if not printed:
            if args.verbose:
                logwrite("Not applying changes from %s, not needed" % (os.path.basename(pdir),))
        else:
            git_debug_snapshot(args, "apply backport patches from %s" % (os.path.basename(pdir),))

    # some post-processing is required
    configtree = kconfig.ConfigTree(os.path.join(args.outdir, 'Kconfig'))
    logwrite('Modify Kconfig tree ...')
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
    f.write('BACKPORTED_KERNEL_VERSION="%s"\n' % kernel_version)
    f.write('BACKPORTED_KERNEL_NAME="%s"\n' % args.base_name)
    f.close()

    symbols = configtree.symbols()

    # write local symbol list -- needed during build
    f = open(os.path.join(args.outdir, '.local-symbols'), 'w')
    for sym in symbols:
        f.write('%s=\n' % sym)
    f.close()

    git_debug_snapshot(args, "add versions/symbols files")

    logwrite('Rewrite Makefiles and Kconfig files ...')

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
        disable_kconfig.append(sym[7:])
        disable_makefile.append(sym[7:])

    configtree.disable_symbols(disable_kconfig)
    git_debug_snapshot(args, "disable impossible kconfig symbols")

    # add kernel version dependencies to Kconfig, from the dependency list
    # we read previously
    for sym in tuple(deplist.keys()):
        new = []
        for dep in deplist[sym]:
            new.append('!BACKPORT_KERNEL_%s' % dep.replace('.', '_'))
        deplist[sym] = new
    configtree.add_dependencies(deplist)
    git_debug_snapshot(args, "add kernel version dependencies")

    # disable things in makefiles that can't be selected and that the
    # build shouldn't recurse into because they don't exist -- if we
    # don't do that then a symbol from the kernel could cause the build
    # to attempt to recurse and fail
    #
    # Note that we split the regex after 50 symbols, this is because of a
    # limitation in the regex implementation (it only supports 100 nested
    # groups -- 50 seemed safer and is still fast)
    regexes = []
    for some_symbols in [disable_makefile[i:i + 50] for i in range(0, len(disable_makefile), 50)]:
        r = '((CPTCFG|CONFIG)_(' + '|'.join([s for s in some_symbols]) + '))'
        regexes.append(re.compile(r, re.MULTILINE))
    for f in maketree.get_makefiles():
        data = open(f, 'r').read()
        for r in regexes:
            data = r.sub(r'IMPOSSIBLE_\3', data)
        fo = open(f, 'w')
        fo.write(data)
        fo.close()
    git_debug_snapshot(args, "disable unsatisfied Makefile parts")

    logwrite('Done!')
    return 0

if __name__ == '__main__':
    ret = _main()
    if ret:
        sys.exit(ret)

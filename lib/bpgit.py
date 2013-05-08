import subprocess, re, os, tempfile

class GitError(Exception):
    pass
class SHAError(GitError):
    pass
class ExecutionError(GitError):
    def __init__(self, errcode):
        self.error_code = errcode

def _check(process):
    if process.returncode != 0:
        raise ExecutionError(process.returncode)

_sha_re = re.compile('^[0-9a-fA-F]*$')

def rev_parse(rev='HEAD', tree=None):
    process = subprocess.Popen(['git', 'rev-parse', rev],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

    sha = stdout.strip()
    if not _sha_re.match(sha):
        raise SHAError()
    return sha

def describe(rev='HEAD', tree=None):
    process = subprocess.Popen(['git', 'describe', '--always', '--long', rev],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

    return stdout.strip()

def init(tree=None):
    process = subprocess.Popen(['git', 'init'],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

def add(path, tree=None):
    process = subprocess.Popen(['git', 'add', path],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

def commit_all(message, tree=None):
    add('.', tree=tree)
    process = subprocess.Popen(['git', 'commit', '--allow-empty', '-a', '-m', message],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

def ls_tree(rev, files, tree=None):
    process = subprocess.Popen(['git', 'ls-tree', '-z', '-r', rev, '--', ] + list(files),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    files = stdout.split('\0')
    ret = []
    for f in files:
        if not f:
            continue
        meta, f = f.split('\t', 1)
        meta = meta.split()
        meta.append(f)
        ret.append(meta)
    process.wait()
    _check(process)
    return ret

def get_blob(blob, outf, tree=None):
    try:
        import git, gitdb
        r = git.Repo(path=tree)
        b = r.rev_parse(blob + '^{blob}')
        b.stream_data(outf)
    except ImportError:
        process = subprocess.Popen(['git', 'show', blob],
                                   stdout=outf, close_fds=True, cwd=tree)
        process.wait()
        _check(process)

def clone(gittree, outputdir, options=[]):
    process = subprocess.Popen(['git', 'clone'] + options + [gittree, outputdir])
    process.wait()
    _check(process)

def set_origin(giturl, gitdir):
    process = subprocess.Popen(['git', 'remote', 'rm', 'origin'],
                               close_fds=True, universal_newlines=True, cwd=gitdir)
    process.wait()

    process = subprocess.Popen(['git', 'remote', 'add', 'origin', giturl],
                               close_fds=True, universal_newlines=True, cwd=gitdir)
    process.wait()
    _check(process)

def remote_update(gitdir):
    process = subprocess.Popen(['git', 'remote', 'update'],
                               close_fds=True, universal_newlines=True, cwd=gitdir)
    process.wait()
    _check(process)

def shortlog(from_commit, to_commit, tree=None):
    process = subprocess.Popen(['git', 'shortlog', from_commit + '..' + to_commit],
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               close_fds=True, universal_newlines=True,
                               cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    return stdout

def commit_env_vars(commitid, tree=None):
    process = subprocess.Popen(['git', 'show', '--name-only',
                                '--format=format:GIT_AUTHOR_NAME=%an%nGIT_AUTHOR_EMAIL=%ae%nGIT_AUTHOR_DATE=%aD%x00',
                                commitid],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                close_fds=True, universal_newlines=True,
                                cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    data = stdout.split('\x00')[0]
    vals = data.split('\n')
    d = {}
    for k, v in map(lambda x: x.split('=', 1), vals):
        d[k] = v
    return d

def commit_message(commitid, tree=None):
    process = subprocess.Popen(['git', 'show', '--name-only',
                                '--format=format:%s%n%n%b%x00', commitid],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                close_fds=True, universal_newlines=True,
                                cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    return stdout.split('\x00')[0]

def remove_config(cfg, tree=None):
    process = subprocess.Popen(['git', 'config', '--unset-all', cfg],
                               close_fds=True, universal_newlines=True, cwd=tree)
    process.wait()
    _check(process)

def ls_remote(branch, tree=None, remote='origin'):
    process = subprocess.Popen(['git', 'ls-remote', '--exit-code', remote, 'refs/heads/' + branch],
                               stdout=subprocess.PIPE,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    sha = stdout.split()[0]
    if not _sha_re.match(sha):
        raise SHAError()
    return sha

def add(fn, tree=None):
    process = subprocess.Popen(['git', 'add', fn], cwd=tree,
                               close_fds=True, universal_newlines=True)
    process.wait()
    _check(process)

def commit(msg, tree=None, env = {}, opts=[]):
    stdin = tempfile.NamedTemporaryFile(mode='wr')
    stdin.write(msg)
    stdin.seek(0)
    process = subprocess.Popen(['git', 'commit', '--file=-'] + opts,
                               stdin=stdin.file, universal_newlines=True, env=env,
                               cwd=tree)
    process.wait()
    _check(process)

def push(opts=[], tree=None):
    process = subprocess.Popen(['git', 'push'] + opts,
                               close_fds=True, universal_newlines=True, cwd=tree)
    process.wait()
    _check(process)

def log_commits(from_commit, to_commit, tree=None):
    process = subprocess.Popen(['git', 'log', '--first-parent', '--format=format:%H',
                                from_commit + '..' + to_commit],
                               stdout=subprocess.PIPE,
                               close_fds=True, universal_newlines=True,
                               cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    vals = stdout.split()
    vals.reverse()
    return vals

def commit_env_vars(commitid, tree=None):
    process = subprocess.Popen(['git', 'show', '--name-only',
                                '--format=format:GIT_AUTHOR_NAME=%an%nGIT_AUTHOR_EMAIL=%ae%nGIT_AUTHOR_DATE=%aD%x00',
                                commitid],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                close_fds=True, universal_newlines=True,
                                cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    data = stdout.split('\x00')[0]
    vals = data.split('\n')
    d = {}
    for k, v in map(lambda x: x.split('=', 1), vals):
        d[k] = v
    return d

def rm(opts=[], tree=None):
    process = subprocess.Popen(['git', 'rm'] + opts,
                               close_fds=True, universal_newlines=True, cwd=tree)
    process.wait()
    _check(process)

def reset(opts=[], tree=None):
    process = subprocess.Popen(['git', 'reset'] + opts,
                               close_fds=True, universal_newlines=True, cwd=tree)
    process.wait()
    _check(process)

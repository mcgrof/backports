import subprocess, re, os

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
    process = subprocess.Popen(['git', 'show', blob],
                               stdout=outf, close_fds=True, cwd=tree)
    process.wait()
    _check(process)

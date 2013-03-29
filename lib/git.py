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
    olddir = os.getcwd()
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
    olddir = os.getcwd()
    process = subprocess.Popen(['git', 'describe', '--always', '--long', rev],
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True, cwd=tree)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)

    return stdout.strip()

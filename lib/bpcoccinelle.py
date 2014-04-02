from multiprocessing import Process, cpu_count, Queue
import subprocess, os
from lib.tempdir import tempdir

class CoccinelleError(Exception):
    pass
class ExecutionError(CoccinelleError):
    def __init__(self, errcode):
        self.error_code = errcode
class ExecutionErrorThread(CoccinelleError):
    def __init__(self, errcode, fn, cocci_file, threads, t, logwrite, print_name):
        self.error_code = errcode
        logwrite("Failed to apply changes from %s" % print_name)

        logwrite("Specific log output from change that failed using %s" % print_name)
        tf = open(fn, 'r')
        for line in tf.read():
            logwrite('> %s' % line)
        tf.close()

        logwrite("Full log using %s" % print_name)
        for num in range(threads):
            fn = os.path.join(t, '.tmp_spatch_worker.' + str(num))
            if (not os.path.isfile(fn)):
                continue
            tf = open(fn, 'r')
            for line in tf.read():
                logwrite('> %s' % line)
            tf.close()
            os.unlink(fn)

def spatch(cocci_file, outdir,
           max_threads, thread_id, temp_dir, ret_q, extra_args=[]):
    cmd = ['spatch', '--sp-file', cocci_file, '--in-place',
            '--backup-suffix', '.cocci_backup', '--dir', '.']

    if (max_threads > 1):
        cmd.extend(['-max', str(max_threads), '-index', str(thread_id)])

    cmd.extend(extra_args)

    fn = os.path.join(temp_dir, '.tmp_spatch_worker.' + str(thread_id))
    outfile = open(fn, 'w')

    sprocess = subprocess.Popen(cmd,
                               stdout=outfile, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True,
                               cwd=outdir)
    sprocess.wait()
    if sprocess.returncode != 0:
        raise ExecutionError(sprocess.returncode)
    outfile.close()
    ret_q.put((sprocess.returncode, fn))

def threaded_spatch(cocci_file, outdir, logwrite, print_name, test_cocci):
    num_cpus = cpu_count()
    threads = num_cpus * 3
    if test_cocci:
        threads = num_cpus * 10
    jobs = list()
    output = ''
    ret_q = Queue()
    with tempdir() as t:

        for num in range(threads):
            p = Process(target=spatch, args=(cocci_file, outdir,
                                             threads, num, t, ret_q))
            jobs.append(p)
        for p in jobs:
            p.start()

        for num in range(threads):
            ret, fn = ret_q.get()
            if ret != 0:
                raise ExecutionErrorThread(ret, fn, cocci_file, threads, t,
                                           logwrite, print_name)

        for job in jobs:
            p.join()

        for num in range(threads):
            fn = os.path.join(t, '.tmp_spatch_worker.' + str(num))
            tf = open(fn, 'r')
            output = output + tf.read()
            tf.close()
            os.unlink(fn)

        output = output + '\n'
        return output

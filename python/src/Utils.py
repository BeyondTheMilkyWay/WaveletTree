import resource
import time

""" Returns maximum memory usage of the process in kB """
def get_max_memory_B():
    return resource.getrusage(resource.RUSAGE_SELF).ru_maxrss


def get_max_memory_kB():
    return get_max_memory_B() / 1024.0


def get_max_memory_MB():
    return get_max_memory_kB() / 1024.0


def write_line(str):
    return str + '\n'


class Stopwatch():
    def __init__(self):
        self.start_time = None
        self.end_time = None

    def start(self):
        self.start_time = time.time()

    def stop(self):
        self.end_time = time.time()

    def restart(self):
        self.start_time = None
        self.end_time = None

    def elapsed_ms(self):
        return (self.end_time - self.start_time) * 1000

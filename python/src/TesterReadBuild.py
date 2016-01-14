import sys

from FASTA import FASTA
from WaveletTree import WaveletTree
import Utils


def report(out_filepath, read_stopwatch, read_memory, build_stopwatch, build_memory):
    """ Write report to file """

    out_file = open(out_filepath, 'w')

    out_file.write(Utils.write_line('report|' + out_filepath))

    out_file.write(Utils.write_line('read|time ' + read_stopwatch.elapsed_ms()))
    out_file.write(Utils.write_line('read|memory ' + str(read_memory) + ' kB'))

    out_file.write(Utils.write_line('build|time ' + build_stopwatch.elapsed_ms()))
    out_file.write(Utils.write_line('build|memory ' + str(build_memory) + ' kB'))

    out_file.close()


""" Tester program that measures time and memory performance of reading data and building tree """
if __name__ == '__main__':

    if len(sys.argv) < 3:
        print 'Missing arguments: <in_file> <out_file>'
        exit(-1)

    # Reading data
    read_stopwatch = Utils.Stopwatch()
    fasta_file = FASTA(sys.argv[1])
    read_stopwatch.start()
    fasta_file.read()
    read_stopwatch.stop()
    read_memory_kB = Utils.get_max_memory_kB()

    alphabet = list(set(fasta_file.data))
    alphabet.sort()

    # Building tree
    build_stopwatch = Utils.Stopwatch()
    tree = WaveletTree()
    build_stopwatch.start()
    tree.build(alphabet, fasta_file.data)
    build_stopwatch.stop()
    build_memory_kB = Utils.get_max_memory_kB()

    report(sys.argv[2], read_stopwatch, read_memory_kB, build_stopwatch, build_memory_kB)

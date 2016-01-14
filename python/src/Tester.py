import sys
import math

from FASTA import FASTA
from WaveletTree import WaveletTree
import Utils


def report_3(read_stopwatch, build_stopwatch, select_avg_time, rank_avg_time, access_avg_time):
    report_2(read_stopwatch, build_stopwatch)

    rank_file = open('rank.out', 'w')
    rank_file.write(str(rank_avg_time))
    rank_file.close()

    access_file = open('access.out', 'w')
    access_file.write(str(access_avg_time))
    access_file.close()

    select_file = open('select.out', 'w')
    select_file.write(str(select_avg_time))
    select_file.close()


def report_2(read_stopwatch, build_stopwatch):
    read_file = open('read.out', 'w')
    read_file.write(str(read_stopwatch.elapsed_ms()))
    read_file.close()

    build_file = open('build.out', 'w')
    build_file.write(str(build_stopwatch.elapsed_ms()))
    build_file.close()


def report(out_filepath, read_stopwatch, read_memory, build_stopwatch, build_memory):
    """ Write report to file """

    out_file = open(out_filepath, 'w')

    out_file.write(Utils.write_line('report|' + out_filepath))

    out_file.write(Utils.write_line('read|time ' + str(read_stopwatch.elapsed_ms())))
    out_file.write(Utils.write_line('read|memory ' + str(read_memory) + ' kB'))

    out_file.write(Utils.write_line('build|time ' + str(build_stopwatch.elapsed_ms())))
    out_file.write(Utils.write_line('build|memory ' + str(build_memory) + ' kB'))

    out_file.close()


""" Tester program that measures time and memory performance of reading data and building tree """
if __name__ == '__main__':

    if len(sys.argv) < 3:
        print 'Missing arguments: <in_file> <query>'
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

    if sys.argv[2] == 'query':
        data_size = len(fasta_file.data)
        test_idx = data_size / 2
        test_character = fasta_file.data[0]
        test_nth_occurence = math.floor(math.sqrt(test_idx))
        test_runs = int(sys.argv[3])

        stopwatch = Utils.Stopwatch()
        time_access = 0
        time_select = 0
        time_rank = 0
        for i in xrange(test_runs):
            # Access
            stopwatch.restart()
            stopwatch.start()
            tree.access(test_idx)
            stopwatch.stop()
            time_access = time_access + stopwatch.elapsed_ms()

            # Select
            stopwatch.restart()
            stopwatch.start()
            tree.select(test_nth_occurence, test_character)
            stopwatch.stop()
            time_select = time_select + stopwatch.elapsed_ms()
            stopwatch.restart()

            # Rank
            stopwatch.start()
            tree.rank(test_idx, test_character)
            stopwatch.stop()
            time_rank += stopwatch.elapsed_ms()

        time_select /= test_runs
        time_rank /= test_runs
        time_access /= test_runs

        report_3(read_stopwatch, build_stopwatch, time_select, time_rank, time_access)

    else:
        report_2(read_stopwatch, build_stopwatch)


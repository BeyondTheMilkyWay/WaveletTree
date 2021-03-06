import sys

from FASTA import FASTA
from WaveletTree import WaveletTree


"""
    Main entry for building and doing queries on WaveletTree data structure
    Program arguments: <file> <task> <task_args...>
        <in_file> - path to input FASTA file
        <out_file> - path to where to write result
        <task> - name of the query to run [access, rank, select]
        <task_args> - arguments for query
"""
if __name__ == '__main__':

    if len(sys.argv) < 4:
        print 'Missing arguments: <in_file> <out_file> <task> <task_args...>'
        exit(-1)

    task = sys.argv[3]

    fasta_file = FASTA(sys.argv[1])
    fasta_file.read()

    alphabet = list(set(fasta_file.data))
    alphabet.sort()

    tree = WaveletTree()
    tree.build(alphabet, fasta_file.data)

    if task == 'access':
        index = int(sys.argv[4])
        result = tree.access(index)

    elif task == 'rank':
        position = int(sys.argv[4])
        character = sys.argv[5]
        result = tree.rank(position, character)

    elif task == 'select':
        nth_occurence = int(sys.argv[4])
        character = sys.argv[5]
        result = tree.select(nth_occurence, character)

    elif task == 'build':
        result = 'OK'

    # Save result to out file
    out_file = open(sys.argv[2], 'w')
    out_file.write(str(result))
    out_file.close()

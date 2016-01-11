import sys

from FASTA import FASTA
from WaveletTree import WaveletTree


if __name__ == '__main__':

    if len(sys.argv) < 3:
        print 'Missing arguments: <file> <task> <task_args...>'
        exit(-1)

    task = sys.argv[2]

    fasta_file = FASTA(sys.argv[1])
    fasta_file.read()

    alphabet = list(set(fasta_file.data))
    alphabet.sort()

    tree = WaveletTree()
    tree.build(alphabet, fasta_file.data)

    if task == 'access':
        index = int(sys.argv[3])
        print tree.access(index)

    elif task == 'rank':
        position = int(sys.argv[3])
        character = sys.argv[4]
        print tree.rank(position, character)

    elif task == 'select':
        nth_occurence = int(sys.argv[3])
        character = sys.argv[4]
        print tree.select(nth_occurence, character)

from FASTA import FASTA
from WaveletTree import WaveletTree

if __name__ == '__main__':

    # TODO read file path from program arguments
    fasta_file = FASTA('../simple.fas')
    fasta_file.read()

    alphabet = list(set(fasta_file.data))
    alphabet.sort()

    tree = WaveletTree()
    tree.build(alphabet, fasta_file.data)

    print 'rank(5, e)', tree.rank(5, 'e')
    print 'access(0)', tree.access(0)

    print 'Done'

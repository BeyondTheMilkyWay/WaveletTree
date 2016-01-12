from FASTA import FASTA
from WaveletTree import WaveletTree


def report_rank(tree):
    print 'Rank simple.fa'

    for c in tree.root_node.alphabet:
        for idx in xrange(len(tree.root_node.bit_vector)):
            print 'rank(%s, %s) = %s' % (idx, c, tree.rank(idx, c))


def report_access(tree):
    print 'Access simple.fa'

    for idx in xrange(len(tree.root_node.bit_vector)):
        print 'access(%s) = %s' % (idx, tree.access(idx))


def report_select(tree):
    print 'Select simple.fa'

    for c in tree.root_node.alphabet:
        for nth_occurence in xrange(10):
            print 'select(%s, %s) = %s' % (nth_occurence, c, tree.select(nth_occurence, c))


if __name__ == '__main__':

    fasta_file = FASTA('../simple.fa')
    fasta_file.read()

    alphabet = list(set(fasta_file.data))
    alphabet.sort()

    tree = WaveletTree()
    tree.build(alphabet, fasta_file.data)

    report_rank(tree)
    report_access(tree)
    report_select(tree)
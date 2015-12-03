
class WaveletNode:

    def __init__(self, alphabet):
        self.bit_vector = ''
        self.alphabet = alphabet
        self.left = None
        self.right = None

    def add(self, bit):
        self.bit_vector += bit

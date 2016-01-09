
class WaveletNode:

    def __init__(self, alphabet, parent=None):
        self.bit_vector = ''
        self.alphabet = alphabet
        self.left = None
        self.right = None
        self.parent = parent

    def add(self, bit):
        self.bit_vector += bit

    def nth_occurence(self, nth_occurence, bit_type):
        occurences = 0
        last_index = -1
        for idx, bit in enumerate(self.bit_vector):
            if bit == bit_type:
                occurences += 1
                last_index = idx

            if occurences == nth_occurence:
                break

        # there is no 'nth_occurence' bits of 'bit_type' in 'bit_vector'
        if occurences != nth_occurence:
            last_index = -1

        return last_index

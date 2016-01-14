import StringIO

from WaveletNode import WaveletNode

"""
    WaveletTree class represents one Wavelet tree data structure
"""
class WaveletTree:
    def __init__(self):
        self.root_node = None

    """ Constracting WaveletTree based on 'data' and 'alphabet' """
    def build(self, alphabet, data):
        self.root_node = WaveletNode(alphabet)
        self.__build(self.root_node, alphabet, data)

    """ Counts number of times 'character' appears in string up to 'position' """
    def rank(self, position, character):
        self.check_position(position)
        self.check_character(character)

        # TODO it will not count character at given 'position'. Does it need to count it?
        return WaveletTree.__rank(self.root_node, position+1, character)

    """ Returns character at 'index' position in string """
    def access(self, index):
        self.check_position(index)

        return WaveletTree.__access(self.root_node, index)

    """ Returns position in string at which 'character' occurs for the 'nth_occurrence' time """
    def select(self, nth_occurrence, character):
        self.check_character(character)

        # Find node that represents 'character'
        tmp_node = self.root_node
        while len(tmp_node.alphabet) != 1:
            is_left = character in tmp_node.left.alphabet
            tmp_node = tmp_node.left if is_left else tmp_node.right

        return WaveletTree.__select(tmp_node.parent, nth_occurrence, character)

    def log(self):
        WaveletTree.__log(self.root_node)

    def check_position(self, position):
        if position > len(self.root_node.bit_vector):
            raise ValueError('Position is greater than bit_vector')

    def check_character(self, character):
        if character not in self.root_node.alphabet:
            raise ValueError('Character is not in alphabet')

    @staticmethod
    # Internal recursive method that builds tree
    def __build(node, alphabet, data):
        if len(alphabet) in [0, 1]:
            return

        half = len(alphabet) / 2

        # Find left && right alphabet
        left_sub_alphabet = alphabet[:half]
        right_sub_alphabet = alphabet[half:]

        # Build bit vector for current node
        buffer = []
        [buffer.append('0' if c in left_sub_alphabet else '1') for c in data]
        node.add(''.join(buffer))

        # Split data for left and right node
        left_sub_data = []
        right_sub_data = []
        for bit in data:
            if bit in left_sub_alphabet:
                left_sub_data.append(bit)
            else:
                right_sub_data.append(bit)

        # Create left && right node and build recursively
        node.left = WaveletNode(left_sub_alphabet, node)
        WaveletTree.__build(node.left, left_sub_alphabet, left_sub_data)
        node.right = WaveletNode(right_sub_alphabet, node)
        WaveletTree.__build(node.right, right_sub_alphabet, right_sub_data)

    @staticmethod
    # Internal recursive method that executes rank query
    def __rank(node, position, character):
        if len(node.alphabet) == 1:
            return position

        is_left = character in node.left.alphabet

        child = node.left if is_left else node.right
        bit_type = '0' if is_left else '1'

        new_position = 0
        for bit in node.bit_vector[:position]:
            if bit == bit_type:
                new_position += 1

        return WaveletTree.__rank(child, new_position, character)

    @staticmethod
    # Internal recursive method that executes access query
    def __access(node, index):
        if len(node.alphabet) == 1:
            return node.alphabet[0]

        is_left = node.bit_vector[index] == '0'
        child = node.left if is_left else node.right
        bit_type = '0' if is_left else '1'

        new_index = 0
        for bit in node.bit_vector[:index]:
            if bit == bit_type:
                new_index += 1

        return WaveletTree.__access(child, new_index)


    @staticmethod
    # Internal recursive method that executes select query
    def __select(node, nth_occurence, character):
        is_left = character in node.left.alphabet
        bit_type = '0' if is_left else '1'

        new_index = node.nth_occurence(nth_occurence, bit_type)

        return new_index if not node.parent else WaveletTree.__select(node.parent, new_index + 1, character)

    @staticmethod
    # Internal recursive helper method for logging node and all its childs
    def __log(node):
        if not node or len(node.bit_vector) == 0:
            return

        print node.bit_vector
        WaveletTree.__log(node.left)
        WaveletTree.__log(node.right)

from WaveletNode import WaveletNode


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

    """ Returns position in string where 'character' occurs for the 'nth_occurrence' time """
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

    # Internal recursive method that builds tree
    @staticmethod
    def __build(node, alphabet, data):
        if len(alphabet) in [0, 1]:
            return

        half = len(alphabet) / 2

        # Find left && right alphabet
        left_sub_alphabet = alphabet[:half]
        right_sub_alphabet = alphabet[half:]

        # Build bit vector for current node
        [node.add('0' if c in left_sub_alphabet else '1') for c in data]

        # Split data for left and right node
        left_sub_data = filter(lambda c: c in left_sub_alphabet, data)
        right_sub_data = filter(lambda c: c in right_sub_alphabet, data)

        # Create left && right node and build recursively
        node.left = WaveletNode(left_sub_alphabet, node)
        WaveletTree.__build(node.left, left_sub_alphabet, left_sub_data)
        node.right = WaveletNode(right_sub_alphabet, node)
        WaveletTree.__build(node.right, right_sub_alphabet, right_sub_data)

    @staticmethod
    def __rank(node, position, character):
        if len(node.alphabet) == 1:
            return position

        is_left = character in node.left.alphabet

        child = node.left if is_left else node.right
        bit_type = '0' if is_left else '1'

        new_position = reduce(lambda count, c: count+1 if c == bit_type else count, node.bit_vector[:position], 0)

        return WaveletTree.__rank(child, new_position, character)

    @staticmethod
    def __access(node, index):
        if len(node.alphabet) == 1:
            return node.alphabet[0]

        is_left = node.bit_vector[index] == '0'
        child = node.left if is_left else node.right
        bit_type = '0' if is_left else '1'

        new_index = reduce(lambda count, c: count+1 if c == bit_type else count, node.bit_vector[:index], 0)

        return WaveletTree.__access(child, new_index)


    @staticmethod
    def __select(node, nth_occurence, character):
        is_left = character in node.left.alphabet
        bit_type = '0' if is_left else '1'

        new_index = node.nth_occurence(nth_occurence, bit_type)

        return new_index if not node.parent else WaveletTree.__select(node.parent, new_index + 1, character)

    @staticmethod
    def __log(node):
        if not node or len(node.bit_vector) == 0:
            return

        print node.bit_vector
        WaveletTree.__log(node.left)
        WaveletTree.__log(node.right)

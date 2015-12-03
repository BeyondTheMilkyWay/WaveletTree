from WaveletNode import WaveletNode


class WaveletTree:
    def __init__(self):
        self.root_node = None

    def build(self, alphabet, data):
        self.root_node = WaveletNode(alphabet)
        self.__build(self.root_node, alphabet, data)

    # Internal recursive method that builds tree
    @staticmethod
    def __build(node, alphabet, data):
        if len(alphabet) == 0:
            return

        if len(alphabet) == 1:
            node.left = WaveletNode(alphabet)
            # TODO Not needed because alphabet has the only char
            # [node.left.add('0' if c in alphabet else '1') for c in data]
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
        node.left = WaveletNode(left_sub_alphabet)
        WaveletTree.__build(node.left, left_sub_alphabet, left_sub_data)
        node.right = WaveletNode(right_sub_alphabet)
        WaveletTree.__build(node.right, right_sub_alphabet, right_sub_data)

    def log(self):
        WaveletTree.__log(self.root_node)

    @staticmethod
    def __log(node):
        if not node or len(node.bit_vector) == 0:
            return

        print node.bit_vector
        WaveletTree.__log(node.left)
        WaveletTree.__log(node.right)

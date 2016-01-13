// WaveletTree implementation.
// Created by dsisejkovic on 10.01.16..
//

#include "WaveletTree.h"

void checkIfLetterAllowed(char letter, char *alphabet, int alphabet_len) {
    bool allowed = FALSE;
    for(int i=0;i< alphabet_len;++i) {
        if (alphabet[i] == letter) {
            allowed = TRUE;
        }
    }

    if (allowed == FALSE) {
        error("Letter not in alphabet!");
    }
}

bool isLeafNode(struct WaveletNode *node) {
    if (node->letter != '\0') {
        return TRUE;
    } else {
        return FALSE;
    }
}

void deleteNode(struct WaveletNode *node) {
    if (isLeafNode(node)) {
        free((void *) node);
        return;
    }

    deleteNode(node->left_child);
    deleteNode(node->right_child);

    freeBitVector(node->bit_vector);
    free((void *) node);
}

void deleteTree(struct WaveletTree *tree) {
    deleteNode(tree->root);
    free((void *) tree);
}

bool getEncodingType(char *complete_alphabet, char letter,
                     int left, int right) {
    int half = (right - left) / 2 +  left;
	return letter <= complete_alphabet[half] ? FALSE : TRUE;
}

// expects bit_vector to be defined
void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int data_str_len, int left, int right) {
    if (bit_vector == NULL) {
        error("BitVector must be defined before encoding.");
    }

	int half = (right - left) / 2 + left;
    for (int i = 0; i < data_str_len; ++i) {
        char letter = data_str_part[i];

        // find if letter on [i] should be 0 or 1 encoded
		bool encoding_value = letter <= complete_alphabet[half] ? FALSE : TRUE;
							
        bitVecSetOnPosition(bit_vector, i, encoding_value);
    }
}

struct WaveletNode *allocateWaveletNode() {
    struct WaveletNode *node = (struct WaveletNode *) malloc(sizeof(struct WaveletNode));
    node->letter = '\0';

    return node;
}

struct WaveletNode *addNode(char *complete_alphabet, char *node_chars, int input_len, int left, int right) {
    struct WaveletNode *node = allocateWaveletNode();
    node->bit_vector = allocateBitVector(input_len);
    encodeToBitVector(node->bit_vector, node_chars, complete_alphabet, input_len, left, right);

    node->alphabet_start = left;
    node->alphabet_end = right;

    if (right - left == 0) {
        // node contains only one type of character
        // it must be a leaf node
        node->letter = complete_alphabet[left];
	}
	else if (right - left == 1) {
        // node with two characters in alphabet
        // has two leafs
		node->left_child = allocateWaveletNode();
		node->left_child->letter = complete_alphabet[left];
		node->left_child->parent = node;

		node->right_child = allocateWaveletNode();
		node->right_child->letter = complete_alphabet[right];
		node->right_child->parent = node;
	}
	else {
        int half = (right - left) / 2;
        int middle = left + half;

		int length = 0;
        char *extracted_left = extractLettersByEncoding(node->bit_vector, node_chars, FALSE, &length);
        node->left_child = addNode(complete_alphabet, extracted_left,length, left, middle);
        node->left_child->parent = node;

        char *extracted_right = extractLettersByEncoding(node->bit_vector, node_chars, TRUE, &length);
        node->right_child = addNode(complete_alphabet, extracted_right, length, middle + 1, right);
        node->right_child->parent = node;

        free((void *) extracted_left);
        free((void *) extracted_right);
    }

    return node;
}

struct WaveletTree *buildTree(char *input_str, int input_len, char *complete_alphabet, int alphabet_len) {
    struct WaveletTree *tree = (struct WaveletTree *) malloc(sizeof(struct WaveletTree));
    tree->root = addNode(complete_alphabet, input_str, input_len, 0, alphabet_len - 1);
    tree->root->parent = NULL;

    return tree;
}

int rankRec(struct WaveletNode *node, char *complete_alphabet,
            char letter, int position) {
    // find encoding of this letter on this level
    bool encoding = getEncodingType(complete_alphabet, letter, node->alphabet_start, node->alphabet_end);

    // calc num of times the encoding appears up to 'position'
    int freq = getOccurrenceCount(node->bit_vector, position, encoding);

    if ((encoding == FALSE && isLeafNode(node->left_child)) ||
            (encoding == TRUE && isLeafNode(node->right_child))) {
        return freq;
    }

    if (encoding == FALSE) {
        return rankRec(node->left_child, complete_alphabet, letter, freq);
    } else {
        return rankRec(node->right_child, complete_alphabet, letter, freq);
    }
}

int rankOp(struct WaveletTree *tree, char *complete_alphabet,
           int position, char letter) {
    checkIfLetterAllowed(letter, complete_alphabet, (int) strlen(complete_alphabet));
    struct WaveletNode *root = tree->root;

    // for root node we take position + 1
    bool encoding = getEncodingType(complete_alphabet, letter, root->alphabet_start, root->alphabet_end);

    // calc num of times the encoding appears up to 'position'
    int freq = getOccurrenceCount(root->bit_vector, position + 1, encoding);
    if (encoding == FALSE) {
        return rankRec(root->left_child, complete_alphabet, letter, freq);
    } else {
        return rankRec(root->right_child, complete_alphabet, letter, freq);
    }
}

char accessRec(struct WaveletNode *node, char *complete_alphabet, int position) {
    bool encoding = bitVecGetOnPosition(node->bit_vector, position);

    if (encoding == FALSE) {
        if (isLeafNode(node->left_child)) {
            return node->left_child->letter;
        }

        int freq = getOccurrenceCount(node->bit_vector, position, encoding);
        return accessRec(node->left_child, complete_alphabet, freq);
    } else {
        if (isLeafNode(node->right_child)) {
            return node->right_child->letter;
        }

        int freq = getOccurrenceCount(node->bit_vector, position, encoding);
        return accessRec(node->right_child, complete_alphabet, freq);
    }
}

char accessOp(struct WaveletTree *tree, char *complete_alphabet, int position) {
    struct WaveletNode *root = tree->root;
    return accessRec(root, complete_alphabet, position);
}

int selectRec(struct WaveletNode *node, char *complete_alphabet,
              char letter, int nth_occurrence) {
    checkIfLetterAllowed(letter, complete_alphabet, (int) strlen(complete_alphabet));
    bool encoding = getEncodingType(complete_alphabet, letter, node->alphabet_start, node->alphabet_end);
    int position = calcNthOccurrence(node->bit_vector, nth_occurrence, encoding);

    if (node->parent == NULL) {
        return position;
    } else {
        return selectRec(node->parent, complete_alphabet, letter, position + 1);
    }
}

int selectOp(struct WaveletTree *tree, char *complete_alphabet, char letter, int nth_occurrence) {
    struct WaveletNode *node = tree->root;

    // find leaf node containing 'letter'
    // bottom-up procedure: find starting node
    while (!isLeafNode(node)) {
        bool encoding = getEncodingType(complete_alphabet, letter, node->alphabet_start, node->alphabet_end);

        if (encoding == FALSE) {
            node = node->left_child;
        } else {
            node = node->right_child;
        }
    }

    return selectRec(node->parent, complete_alphabet, letter, nth_occurrence);
}
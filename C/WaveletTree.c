//
// Created by dsisejkovic on 10.01.16..
//

#include "WaveletTree.h"

bool isLeafNode(struct WaveletNode *node) {
    if (node->letter == '\0') {
        return FALSE;
    } else {
        return TRUE;
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
    int half = (right - left) / 2;

    int index = 0;
    while (letter != complete_alphabet[left + index]) {
        ++index;
    }

    return (index <= half) ? FALSE : TRUE;
}

// expects bit_vector to be defined
void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int left, int right) {
    if (bit_vector == NULL) {
        error("BitVector must be defined before encoding.");
    }

    for (int i = 0; i < strlen(data_str_part); ++i) {
        char letter = data_str_part[i];

        // find if letter on [i] should be 0 or 1 encoded
        bool encoding_value = getEncodingType(complete_alphabet, letter, left, right);
        bitVecSetOnPosition(bit_vector, i, encoding_value);
    }
}

struct WaveletNode *allocateWaveletNode() {
    struct WaveletNode *node = (struct WaveletNode *) malloc(sizeof(struct WaveletNode));
    node->letter = '\0';

    return node;
}

struct WaveletNode *addNode(char *complete_alphabet, char *node_chars,
                            int left, int right) {
    struct WaveletNode *node = allocateWaveletNode();
    node->bit_vector = allocateBitVector(strlen(node_chars));
    encodeToBitVector(node->bit_vector, node_chars, complete_alphabet, left, right);

    node->alphabet_start = left;
    node->alphabet_end = right;

    if (right - left == 1) {
        node->left_child = allocateWaveletNode();
        node->left_child->letter = complete_alphabet[left];

        node->right_child = allocateWaveletNode();
        node->right_child->letter = complete_alphabet[right];
    } else {
        int half = (right - left) / 2;
        int middle = left + half;

        char *extracted_left = extractLettersByEncoding(node->bit_vector, node_chars, FALSE);
        node->left_child = addNode(complete_alphabet, extracted_left, left, middle);

        char *extracted_right = extractLettersByEncoding(node->bit_vector, node_chars, TRUE);
        node->right_child = addNode(complete_alphabet, extracted_right, middle, right);

        free((void *) extracted_left);
        free((void *) extracted_right);
    }

    return node;
}

struct WaveletTree *buildTree(char *input_str, char *complete_alphabet) {
    struct WaveletTree *tree = (struct WaveletTree *) malloc(sizeof(struct WaveletTree));
    tree->root = addNode(complete_alphabet, input_str, 0, (int) (strlen(complete_alphabet) - 1));

    return tree;
}

int rankRec(struct WaveletNode *node, char *complete_alphabet,
            char letter, int position) {
    // find encoding of this letter on this level
    bool encoding = getEncodingType(complete_alphabet, letter, node->alphabet_start, node->alphabet_end);

    // calc num of times the encoding appears up to 'position'
    int freq = getOccurrenceCount(node->bit_vector, position, encoding);

    if (isLeafNode(node->left_child) || isLeafNode(node->right_child)) {
        return freq;
    }

    if (encoding == FALSE) {
        return rankRec(node->left_child, complete_alphabet, letter, freq);
    } else {
        return rankRec(node->right_child, complete_alphabet, letter, freq);
    }
}

int rank(struct WaveletTree *tree, char *complete_alphabet,
         int position, char letter) {
    struct WaveletNode *root = tree->root;
    return rankRec(root, complete_alphabet, letter, position + 1);
}

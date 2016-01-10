//
// Created by dsisejkovic on 10.01.16..
//

#include "WaveletTree.h"
#include "Utils.h"

bool isLeafNode(struct WaveletNode *node) {
    if (node->letter == '\0') {
        return FALSE;
    } else {
        return TRUE;
    }
}

// this will probably need "**"
// expects bit_vector to be defined
void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int left, int right) {
    if (bit_vector == NULL) {
        error("BitVector must be defined before encoding.");
    }

    int half = (right - left) / 2;

    for (int i = 0; i < strlen(data_str_part); ++i) {
        // find if letter on [i] should be 0 or 1 encoded
        char letter = data_str_part[i];

        int index = 0;
        while (letter != complete_alphabet[left + index]) {
            ++index;
        }

        if (index <= half) {
            bitVecSetOnPosition(bit_vector, i, FALSE);
        } else {
            bitVecSetOnPosition(bit_vector, i, TRUE);
        }
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

    // check if this is leaf node
    if ((right - left) == 1) {
        node->left_child = allocateWaveletNode();
        node->left_child->letter = complete_alphabet[left];

        node->right_child = allocateWaveletNode();
        node->right_child->letter = complete_alphabet[right];
    } else {
        node->bit_vector = allocateBitVector(strlen(node_chars));
        encodeToBitVector(node->bit_vector, node_chars, complete_alphabet, left, right);

        node->alphabet_start = left;
        node->alphabet_end = right;

        // extract needed string according to bits and proceed recursion
        int half = (right - left) / 2;
        int middle = left + half;
        node->left_child = addNode(complete_alphabet, extractLettersByEncoding(node->bit_vector, node_chars, FALSE),
                                   left, middle);
        node->right_child = addNode(complete_alphabet, extractLettersByEncoding(node->bit_vector, node_chars, TRUE),
                                    ++middle, right);
    }

    free((void *) node_chars);

    return node;
}

struct WaveletTree *buildTree(char *input_str, char *complete_alphabet) {
    struct WaveletTree *tree = (struct WaveletTree *) malloc(sizeof(struct WaveletTree));
    tree->root = addNode(complete_alphabet, input_str, 0, (int) (strlen(complete_alphabet) - 1));

    return tree;
}

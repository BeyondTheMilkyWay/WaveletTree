// WaveletTree implementation.
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

struct WaveletNode *addNode(char **complete_alphabet, char **node_chars,
                            int left, int right) {
    printf("tu sam");
    struct WaveletNode *node = allocateWaveletNode();
    printf("build bit vector");

    node->bit_vector = allocateBitVector(strlen(node_chars));

    printf("encode");
    encodeToBitVector(node->bit_vector, *node_chars, *complete_alphabet, left, right);


    printf("%d\n", (int) strlen(*complete_alphabet));
    printf("tu");


    node->alphabet_start = left;
    node->alphabet_end = right;

    if (right - left == 1) {
        node->left_child = allocateWaveletNode();
        node->left_child->letter = *complete_alphabet[left];
        node->left_child->parent = node;

        node->right_child = allocateWaveletNode();
        node->right_child->letter = *complete_alphabet[right];
        node->right_child->parent = node;
    } else {
        int half = (right - left) / 2;
        int middle = left + half;

        char *extracted_left = extractLettersByEncoding(node->bit_vector, *node_chars, FALSE);
        node->left_child = addNode(complete_alphabet, &extracted_left, left, middle);
        node->left_child->parent = node;

        char *extracted_right = extractLettersByEncoding(node->bit_vector, *node_chars, TRUE);
        node->right_child = addNode(complete_alphabet, &extracted_right, middle, right);
        node->right_child->parent = node;

        free((void *) extracted_left);
        free((void *) extracted_right);
    }

    return node;
}

struct WaveletTree *buildTree(char **input_str, char **complete_alphabet) {
    struct WaveletTree *tree = (struct WaveletTree *) malloc(sizeof(struct WaveletTree));
    tree->root = addNode(complete_alphabet, input_str, 0, (int) (strlen(*complete_alphabet) - 1));
    tree->root->parent = NULL;

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

int rankOp(struct WaveletTree *tree, char *complete_alphabet,
           int position, char letter) {
    struct WaveletNode *root = tree->root;
    return rankRec(root, complete_alphabet, letter, position + 1);
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
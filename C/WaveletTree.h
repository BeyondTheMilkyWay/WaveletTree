//
// Created by dsisejkovic on 09.01.16..
//

#ifndef C_WAVELET_TREE_H
#define C_WAVELET_TREE_H

#include "BitVector.h"
#include "Basic.h"

struct WaveletNode {
    struct WaveletNode *left_child;
    struct WaveletNode *right_child;
    struct BitVector *bit_vector;
    int alphabet_start;
    int alphabet_end;
    char letter; // if leaf
};

struct WaveletTree {
    struct WaveletNode *root;
};

bool isLeafNode(struct WaveletNode *node);

void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int left, int right);

struct WaveletNode *allocateWaveletNode();

struct WaveletNode *addNode(char *complete_alphabet, char *node_chars,
                            int left, int right);

struct WaveletTree *buildTree(char *input_str, char *complete_alphabet);

#endif //C_WAVELET_TREE_H

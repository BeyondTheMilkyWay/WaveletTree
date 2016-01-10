//
// Created by dsisejkovic on 09.01.16..
//

#ifndef C_WAVELET_TREE_H
#define C_WAVELET_TREE_H

#include "BitVector.h"
#include "Basic.h"

struct WaveletNode {
    struct WaveletNode *parent;
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


void deleteNode(struct WaveletNode *node);

void deleteTree(struct WaveletTree *tree);

bool isLeafNode(struct WaveletNode *node);

bool getEncodingType(char *complete_alphabet, char letter,
                     int left, int right);

void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int left, int right);

struct WaveletNode *allocateWaveletNode();

struct WaveletNode *addNode(char *complete_alphabet, char *node_chars,
                            int left, int right);

struct WaveletTree *buildTree(char *input_str, char *complete_alphabet);

int rankRec(struct WaveletNode *node, char *complete_alphabet,
            char letter, int position);

int rankOp(struct WaveletTree *tree, char *complete_alphabet,
           int position, char letter);

char accessRec(struct WaveletNode *node, char *complete_alphabet, int position);

char accessOp(struct WaveletTree *tree, char *complete_alphabet, int position);

int selectRec(struct WaveletNode *node, char *complete_alphabet,
              char letter, int nth_occurrence);

int selectOp(struct WaveletTree *tree, char *complete_alphabet,
             char letter, int nth_occurrence);

#endif //C_WAVELET_TREE_H

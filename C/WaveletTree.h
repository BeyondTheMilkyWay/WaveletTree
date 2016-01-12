//
// Created by dsisejkovic on 09.01.16..
//

#ifndef C_WAVELET_TREE_H
#define C_WAVELET_TREE_H

#include "BitVector.h"
#include "Basic.h"

/**
 * Represents one wavelet tree node.
 */
struct WaveletNode {
    struct WaveletNode *parent;
    struct WaveletNode *left_child;
    struct WaveletNode *right_child;
    struct BitVector *bit_vector;
    int alphabet_start; // first used index in alphabet
    int alphabet_end;  // last used index in alphabet
    char letter; // if leaf
};

/**
 * Represents a wavelet tree.
 */
struct WaveletTree {
    struct WaveletNode *root;
};

/**
 * Deletes node data and frees memory.
 */
void deleteNode(struct WaveletNode *node);

/**
 * Deletes entire tree structure.
 */
void deleteTree(struct WaveletTree *tree);

/**
 * Checks if 'node' is a leaf node.
 */
bool isLeafNode(struct WaveletNode *node);

/**
 * Gets encoding type (0 or 1) of character 'letter' according to current node
 * properties and used alphabet.
 */
bool getEncodingType(char *complete_alphabet, char letter,
                     int left, int right);

/**
 * Encodes the given 'data_str_part' according to current node properties
 * and the used alphabet.
 */
void encodeToBitVector(struct BitVector *bit_vector, char *data_str_part,
                       char *complete_alphabet, int left, int right);

/**
 * Returns pointer to newly allocated Wavelet node.
 */
struct WaveletNode *allocateWaveletNode();

/**
 * Returns pointer to a newly allocated Wavelet node with appropriate data.
 */
struct WaveletNode *addNode(char **complete_alphabet, char **node_chars,
                            int left, int right);

/**
 * Build an entire Wavelet tree structure according to
 * used alphabet and input stream.
 */
struct WaveletTree *buildTree(char **input_str, char **complete_alphabet);

/**
 * Recursive rank calculation helper function.
 */
int rankRec(struct WaveletNode *node, char *complete_alphabet,
            char letter, int position);

/**
 * Calculates rank of character 'letter'.
 * Counts the number of times the given character appears in string
 * up to 'position'.
 */
int rankOp(struct WaveletTree *tree, char *complete_alphabet,
           int position, char letter);

/**
 * Recursive access calculation helper function.
 */
char accessRec(struct WaveletNode *node, char *complete_alphabet, int position);

/**
 * Returns character at 'position' of string the tree was build upon.
 */
char accessOp(struct WaveletTree *tree, char *complete_alphabet, int position);

/**
 * Recursive select calculation helper function.
 */
int selectRec(struct WaveletNode *node, char *complete_alphabet,
              char letter, int nth_occurrence);

/**
 * Calculates and returns position in string where the character 'letter'
 * appears for the 'nth_occurrence' time.
 */
int selectOp(struct WaveletTree *tree, char *complete_alphabet,
             char letter, int nth_occurrence);

#endif //C_WAVELET_TREE_H

// Defines a bitvector implementation with all necessary manipulation functions.
// Created by dsisejkovic on 10.01.16..
//

#ifndef C_BITVECTOR_H
#define C_BITVECTOR_H

#include "Basic.h"
#include <stdio.h>
#include "Utils.h"

struct BitVector {
    char *bits;
    int size;  // number of bits actually used
};

/**
 * Allocates BitVector of size 'num_of_chars'.
 * Function will calculate optimal character number.
 */
struct BitVector *allocateBitVector(size_t num_of_chars);

/**
 * Sets bit on position 'index' to given 'value'.
 * Index must be ordinary index: function will calculate index with offset.
 */
void bitVecSetOnPosition(struct BitVector *bit_vector, int index, bool value);

/**
 * Gets value of bit on position 'index'.
 * Index must be ordinary index: function will calculate index with offset.
 */
bool bitVecGetOnPosition(struct BitVector *bit_vector, int index);

/**
 * Returns character array containing all characters encoded by given value.
 */
char *extractLettersByEncoding(struct BitVector *bit_vector, char *node_chars, bool value);

/**
 * Deletes given 'bit_vector' and frees memory.
 */
void freeBitVector(struct BitVector *bit_vector);

/**
 * Prints all bits of the given 'bit_vector'.
 */
void printBitVector(struct BitVector *bit_vector);

/**
 * Returns bitvector string representation.
 */
char *getBitVectorAsString(struct BitVector *bit_vector);

/**
 * Calculates num of occurrences of given 'value' in bit_vector.
 */
int getOccurrenceCount(struct BitVector *bit_vector, int max_position, bool value);

/**
 * Calculates num of occurrences of given 'value' in bit_vector.
 * The same approach is used in function 'getOccurrenceCount'.
 */
int calcNthOccurrence(struct BitVector *bit_vector, int nth_occurrence, bool value);

#endif //C_BITVECTOR_H

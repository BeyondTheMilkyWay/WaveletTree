//
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

struct BitVector *allocateBitVector(size_t num_of_chars);

void bitVecSetOnPosition(struct BitVector *bit_vector, int index, bool value);

bool bitVecGetOnPosition(struct BitVector *bit_vector, int index);

char *extractLettersByEncoding(struct BitVector *bit_vector, char *node_chars, bool value);

void freeBitVector(struct BitVector *bit_vector);

void printBitVector(struct BitVector *bit_vector);

char *getBitVectorAsString(struct BitVector *bit_vector);

int getOccurrenceCount(struct BitVector *bit_vector, int max_position, bool value);

int calcNthOccurrence(struct BitVector *bit_vector, int nth_occurrence, bool value);

#endif //C_BITVECTOR_H

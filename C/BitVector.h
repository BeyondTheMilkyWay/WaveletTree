//
// Created by dsisejkovic on 10.01.16..
//

#ifndef C_BITVECTOR_H
#define C_BITVECTOR_H

#include "Basic.h"
#include <sys/types.h>
#include <stdio.h>

struct BitVector {
    char *bits;
    int size;  // number of bits actually used
};

struct BitVector *allocateBitVector(size_t num_of_chars);
void bitVecSetOnPosition(struct BitVector *bit_vector, int index, bool value);
bool bitVecGetOnPosition(struct BitVector *bit_vector, int index);
char *extractLettersByEncoding(struct BitVector *bit_vector, char *node_chars, bool value);
void freeBitVector(struct BitVector *bit_vector);

#endif //C_BITVECTOR_H

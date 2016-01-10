//
// Created by dsisejkovic on 10.01.16..
//
#include "BitVector.h"

struct BitVector *allocateBitVector(size_t num_of_chars) {
    int calc_num = (int) (num_of_chars / 8);

    if (calc_num == 0) {
        calc_num = 1;
    }

    struct BitVector *bit_vector = (struct BitVector *) malloc(sizeof(struct BitVector));
    bit_vector->bits = (char *) malloc(calc_num * sizeof(char));
    bit_vector->size = (int) num_of_chars;

    return bit_vector;
}

void bitVecSetOnPosition(struct BitVector *bit_vector, int index, bool value) {
    int array_index = index / 8;
    int bit_index = index % 8;

    if (value == TRUE) {
        bit_vector->bits[array_index] |= (1 << (7 - bit_index));
    } else {
        bit_vector->bits[array_index] &= ~(1 << (7 - bit_index));
    }
}

bool bitVecGetOnPosition(struct BitVector *bit_vector, int index) {
    int array_index = index / 8;
    int bit_index = index % 8;

    return (bit_vector->bits[array_index] >> (7 - bit_index)) & 1;
}

char *extractLettersByEncoding(struct BitVector *bit_vector, char *node_chars, bool value) {
    int num_of_selected = 0;

    for (int i = 0; i < bit_vector->size; ++i) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            ++num_of_selected;
        }
    }

    char *selected = (char *) malloc((num_of_selected + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < bit_vector->size; i++) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            selected[index] = node_chars[i];
            ++index;
        }
    }

    selected[num_of_selected] = '\0';

    return selected;
}

void printBitVector(struct BitVector *bit_vector) {
    int size = bit_vector->size;
    for (int i = 0; i < size; ++i) {
        printf("%d", bitVecGetOnPosition(bit_vector, i));
    }
    printf("\n");
}

void freeBitVector(struct BitVector *bit_vector) {
    free((void *) bit_vector->bits);
    free((void *) bit_vector);
}

char *getBitVectorAsString(struct BitVector *bit_vector) {
    char *str = (char *) malloc((bit_vector->size + 1) * sizeof(char));

    for (int i = 0; i < bit_vector->size; ++i) {
        str[i] = (char) ((bitVecGetOnPosition(bit_vector, i) == TRUE) ? '1' : '0');
    }

    str[bit_vector->size] = '\0';

    return str;
}

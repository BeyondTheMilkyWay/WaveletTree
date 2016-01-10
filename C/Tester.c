//
// Created by dsisejkovic on 10.01.16..
//

#include <assert.h>
#include "Tester.h"
#include "Utils.h"


void print(char *msg) {
    printf("|%s\n", msg);
}

void testBitVector() {
    char testString[6] = "dthklh";
    char *alphabet = extractAlphabetLetters(testString);

    assert(alphabet[0] == 'd');
    assert(alphabet[1] == 'h');
    assert(alphabet[2] == 'k');
    assert(alphabet[3] == 'l');
    assert(alphabet[4] == 't');

    struct BitVector *bit_vector = allocateBitVector(strlen(testString));
    encodeToBitVector(bit_vector, testString, alphabet, 0, (int) (strlen(alphabet)));

    assert(bit_vector->size == strlen(testString));

    assert(bitVecGetOnPosition(bit_vector, 0) == 0);
    assert(bitVecGetOnPosition(bit_vector, 1) == 1);
    assert(bitVecGetOnPosition(bit_vector, 2) == 0);
    assert(bitVecGetOnPosition(bit_vector, 3) == 0);
    assert(bitVecGetOnPosition(bit_vector, 4) == 1);
    assert(bitVecGetOnPosition(bit_vector, 5) == 0);

    free((void *) alphabet);
    freeBitVector(bit_vector);

    print("BitVector tests [PASSED]");
}

void testAll() {
    testBitVector();
}
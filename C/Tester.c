//
// Created by dsisejkovic on 10.01.16..
//

#include <assert.h>
#include "Tester.h"

void print(char *msg) {
    printf("|%s\n", msg);
}

void testBitVector() {
    char testString[7] = "dthklh";
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

void testTreeBuilding() {
    char tmp[] = "ahcbedghcfaehcgd";
    char *test = (char *) malloc(strlen(tmp) * sizeof(char));
    strcpy(test, tmp);

    char *used_alphabet = extractAlphabetLetters(test);
    struct WaveletTree *tree = buildTree(test, used_alphabet);

    assert(compareStrings(getBitVectorAsString(tree->root->bit_vector), "0100101101011010") == TRUE);

    struct WaveletNode *left_node = tree->root->left_child;
    assert(compareStrings(getBitVectorAsString(left_node->bit_vector), "01011011") == TRUE);

    struct WaveletNode *right_node = tree->root->right_child;
    assert(compareStrings(getBitVectorAsString(right_node->bit_vector), "10110011") == TRUE);

    struct WaveletNode *left_left_node = tree->root->left_child->left_child;
    assert(compareStrings(getBitVectorAsString(left_left_node->bit_vector), "010") == TRUE);

    print("TreeBuild tests [PASSED]");

    free((void *) test);
    deleteTree(tree);
}

void testReplace() {
    char *test = (char *) malloc(7 * sizeof(char));
    test[0] = 'a';
    test[1] = 'b';
    test[2] = ' ';
    test[3] = ' ';
    test[4] = 'd';
    test[5] = ' ';
    test[6] = '\0';

    replaceSpaces(test);

    assert(test[2] == '_');
    assert(test[3] == '_');
    assert(test[5] == '_');

    print("ReplaceSpaces tests [PASSED]");

    free((void *) test);
}

void testRanking() {
    char tmp[] = "Peter_Piper_picked_a_peck_of_pickled_peppers$";
    char *test = (char *) malloc(strlen(tmp) * sizeof(char));
    strcpy(test, tmp);

    char *used_alphabet = extractAlphabetLetters(test);
    struct WaveletTree *tree = buildTree(test, used_alphabet);

    assert(rank(tree,used_alphabet, 5, 'e') == 2);
    assert(rank(tree,used_alphabet, 0, '$') == 0);
    assert(rank(tree,used_alphabet, 15, '$') == 0);
    assert(rank(tree,used_alphabet, 43, '$') == 0);
    assert(rank(tree,used_alphabet, 44, '$') == 1);
    assert(rank(tree,used_alphabet, 28, 'P') == 2);
    assert(rank(tree,used_alphabet, 33, 'P') == 2);
    assert(rank(tree,used_alphabet, 44, 'P') == 2);
    assert(rank(tree,used_alphabet, 38, 'p') == 5);
    assert(rank(tree,used_alphabet, 44, 't') == 1);

    print("Ranking tests [PASSED]");

    free((void *) test);
    deleteTree(tree);
}

void testAll() {
    testReplace();
    testBitVector();
    testTreeBuilding();
    testRanking();
}
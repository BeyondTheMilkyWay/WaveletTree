//
// Created by dsisejkovic on 09.01.16..
//
#include "Basic.h"
#include "WaveletTree.h"
#include "Utils.h"
#include "Tester.h"


int main() {
    const char *file_name = "input.txt";
    char *input;
    char *used_alphabet;
    getAlphabetFromFile(file_name, &used_alphabet, &input);
    printf("%s\n", input);
    printf("%s\n", used_alphabet);


    testAll();
//    struct WaveletTree *tree = buildTree(input, used_alphabet);


    free((void *) input);
//    free((void *) tree);
    return 0;
}

//
// Created by dsisejkovic on 13.01.16..
//

#include "BatchTester.h"
#include "Timer.h"
#include "WaveletTree.h"

void batchTest(char *file_name, char *out_file_name, int num_of_runs) {
    logln("Reading input data...");

    int input_len;
    int alphabet_len;
    char *input;
    char *used_alphabet;
    getAlphabetFromFile(file_name, &used_alphabet, &input, &input_len, &alphabet_len);

    logln("Starting batch mode testing...");

    FILE *file = fopen(out_file_name, "w");
    fputs("# time in ms\n", file);

    for (int i = 0; i < num_of_runs; ++i) {
        printf("|Batch %d...", i);

        timerStart();
        struct WaveletTree *tree = buildTree(input, input_len, used_alphabet, alphabet_len);
        timerStop();

        double time_span = timerGetTimeSpan();
        printf("[%f ms]\n", time_span);

        deleteTree(tree);

        fprintf(file, "%f\n", time_span);
    }

    logln("Batch testing finished.");
    printf("|Result written to: %s", out_file_name);

    fclose(file);
}

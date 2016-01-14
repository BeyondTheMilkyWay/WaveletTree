//
// Created by dsisejkovic on 09.01.16..
//
#include <stdio.h>
#include "Basic.h"
#include "WaveletTree.h"
#include "Tester.h"
#include "Timer.h"
#include "BatchTester.h"
#include <math.h>


void generateFunctionTest(char *input_file) {
    char *input;
    char *used_alphabet;

    int input_len;
    int alphabet_len;

    getAlphabetFromFile(input_file, &used_alphabet, &input, &input_len, &alphabet_len);
    struct WaveletTree *tree = buildTree(input, input_len, used_alphabet, alphabet_len);

    input_len--;
    char letter = input[0];
    int access_index = input_len / 2;
    int rank_index = input_len / 2;
    int select_index = (int) sqrt(input_len / 2);
    int iter = 1000;

    // access tests
    double access_time = 0;
    for (int i = 0; i < iter; ++i) {
        timerStart();
        accessOp(tree, used_alphabet, access_index);
        timerStop();
        access_time += timerGetTimeSpan();
    }

    FILE *access_file = fopen("access.out", "w");
    fprintf(access_file, "%f", access_time / 1000.0);
    fclose(access_file);

    // rank tests
    double rank_time = 0;
    for (int i = 0; i < iter; ++i) {
        timerStart();
        rankOp(tree, used_alphabet, rank_index, letter);
        timerStop();
        rank_time += timerGetTimeSpan();
    }

    FILE *rank_file = fopen("rank.out", "w");
    fprintf(rank_file, "%f", rank_time / 1000.0);
    fclose(rank_file);


    // select tests
    double select_time = 0;
    for (int i = 0; i < iter; ++i) {
        timerStart();
        selectOp(tree, used_alphabet, letter, select_index);
        timerStop();
        select_time += timerGetTimeSpan();
    }

    FILE *select_file = fopen("select.out", "w");
    fprintf(select_file, "%f", select_time / 1000.0);
    fclose(select_file);


    deleteTree(tree);
}

/**
 * Arguments: <input-file-path> <query-type> <args>
 * - <input-file-path> access <index>
 * - <input-file-path> rank <character> <index>
 * - <input-file-path> select <character> <index>
 * - test
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("|c-wavelet tree instructions\n");
        printf("|---------------------------\n");
        printf(" - <input-file-path> access <index>\n");
        printf(" - <input-file-path> rank <index> <character>\n");
        printf(" - <input-file-path> select <index> <character>\n");
        printf(" - batchtest <input-file-path> <output-file> <num-of-runs>\n");
        printf(" - generate-tests <input-file-path>");
        printf(" - function-tests <input-file-path>\n");
        return 0;
    }

    if (strcmp(argv[1], "test") == 0) {
        testAll();
    } else if (strcmp(argv[1], "function-tests") == 0) {
        generateFunctionTest(argv[2]);
    } else if (strcmp(argv[1], "generate-tests") == 0) {
        logln("-----------------------------");
        logln("Generating tests");
        logln("-----------------------------");
        generateReadTest(argv[2], "read.out");
        generateBuildTest(argv[2], "build.out");
    } else if (strcmp(argv[1], "batchtest") == 0) {
        logln("-----------------------------");
        logln("Batch time testing");
        logln("-----------------------------");
        batchTest(argv[2], argv[3], atoi(argv[4]));
    } else {
        char *file_name = argv[1];
        char *input;
        char *used_alphabet;

        logln("Reading input data...");
        int input_len;
        int alphabet_len;

        getAlphabetFromFile(file_name, &used_alphabet, &input, &input_len, &alphabet_len);

        logln("Building tree...");

        timerStart();
        struct WaveletTree *tree = buildTree(input, input_len, used_alphabet, alphabet_len);
        timerStop();

//        printf("|Memory in use: %d MB\n", getValue() / 1024);

        printf("|Execution time [tree building]: %f ms\n", timerGetTimeSpan());

        timerStart();
        char *query = argv[2];
        char *result = (char *) malloc(100 * sizeof(char));
        if (strcmp(query, "access") == 0) {
            int index = atoi(argv[3]);
            char access = accessOp(tree, used_alphabet, index);

            snprintf(result, 25, "access(%d) = %c", index, access);
            printf("|access(%d) = %c\n", index, access);
        } else if (strcmp(query, "rank") == 0) {
            char *character = argv[4];
            int index = atoi(argv[3]);

            int rank = rankOp(tree, used_alphabet, index, *character);
            snprintf(result, 25, "rank(%d, %c) = %d", index, *character, rank);
            printf("|rank(%d, %c) = %d\n", index, *character, rank);
        } else if (strcmp(query, "select") == 0) {
            char *character = argv[4];
            int index = atoi(argv[3]);
            int select = selectOp(tree, used_alphabet, *character, index);

            snprintf(result, 25, "select(%d, %c) = %d", index, *character, select);
            printf("|select(%d, %c) = %d\n", index, *character, select);
        } else {
            error("Unknown query given.");
        }

        timerStop();

        printf("|Execution time [%s]: %f ms\n", query, timerGetTimeSpan());

        char *result_file_name = (char *) malloc((strlen(query) + 1) * sizeof(char));
        strcpy(result_file_name, query);
        strcat(result_file_name, "-res.txt");

        FILE *file = fopen(result_file_name, "w");
        fputs(result, file);

        printf("|Result written to file: %s\n", result_file_name);

        free(result_file_name);
        free((void *) used_alphabet);
        free((void *) result);
        free((void *) input);
        free((void *) tree);
        fclose(file);
    }

    return 0;
}



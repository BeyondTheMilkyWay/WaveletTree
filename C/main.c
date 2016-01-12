//
// Created by dsisejkovic on 09.01.16..
//
#include <stdio.h>
#include "Basic.h"
#include "WaveletTree.h"
#include "Tester.h"
#include "Timer.h"



void logn(char* msg)
{
    printf("|%s\n", msg);
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
        printf(" - test\n");
        return 0;
    }

    if (strcmp(argv[1], "test") == 0) {
        testAll();
    } else {
        char *file_name = argv[1];
        char *input;
        char *used_alphabet;

        logn("Reading input data...");
        getAlphabetFromFile(file_name, &used_alphabet, &input);


        printf("%d", (int) strlen(input));
        printf("ne radi\n");
        printf("%d", (int) strlen(used_alphabet));

        logn("Building wavelet tree...");
        timerStart();
        struct WaveletTree *tree = buildTree(&input, &used_alphabet);
        timerStop();
        printf("Execution time [build]: %f ms\n", timerGetTimeSpan());

        char *query = argv[2];
        char *result = (char *) malloc(25 * sizeof(char));
        if (strcmp(query, "access") == 0) {
            int index = atoi(argv[3]);
            timerStart();
            char access = accessOp(tree, used_alphabet, index);
            timerStop();

            printf("Execution time: %f ms\n", timerGetTimeSpan());
            snprintf(result, 25, "access(%d) = %c", index, access);
            printf("|access(%d) = %c\n", index, access);
        } else if (strcmp(query, "rank") == 0) {
            int index = atoi(argv[3]);
            char *character = argv[4];
            int rank = rankOp(tree, used_alphabet, index, *character);

            snprintf(result, 25, "rank(%d, %c) = %d", index, *character, rank);
            printf("|rank(%d, %c) = %d\n", index, *character, rank);
        } else if (strcmp(query, "select") == 0) {
            int index = atoi(argv[3]);
            char *character = argv[4];
            int select = selectOp(tree, used_alphabet, *character, index);

            snprintf(result, 25, "select(%d, %c) = %d", index, *character, select);
            printf("|select(%d, %c) = %d\n", index, *character, select);
        } else {
            error("Unknown query given.");
        }

        char *result_file_name = query;
        strcat(result_file_name, "-res.txt");

        FILE *file = fopen(result_file_name, "w");
        fputs(result, file);

        printf("|Result written to file: %s\n", result_file_name);

        free((void *) used_alphabet);
        free((void *) result);
        free((void *) input);
        free((void *) tree);
        fclose(file);
    }

    return 0;
}

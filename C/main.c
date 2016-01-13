//
// Created by dsisejkovic on 09.01.16..
//
#include <stdio.h>
#include "Basic.h"
#include "WaveletTree.h"
#include "Tester.h"
#include "Timer.h"


void logln(char *msg) {
    printf("|%s\n", msg);
}


int parseLine(char *line) {
    int i = (int) strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i - 3] = '\0';
    i = atoi(line);
    return i;
}


int getValue() { //Note: this value is in KB!
    FILE *file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];


    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "VmSize:", 7) == 0) {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
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

        logln("Reading input data...");
        int input_len;
        int alphabet_len;

        getAlphabetFromFile(file_name, &used_alphabet, &input, &input_len, &alphabet_len);

        logln("Building tree...");

        timerStart();
        struct WaveletTree *tree = buildTree(input, input_len, used_alphabet, alphabet_len);
        timerStop();

        printf("|Memory in use: %d MB\n", getValue()/ 1024);

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

        char *result_file_name = (char *) malloc(strlen(query + 1) * sizeof(char));
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



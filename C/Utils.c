//
// Created by dsisejkovic on 10.01.16..
//

#include "Utils.h"

void error(const char *msg) {
    printf("|%s\n", msg);
    exit(-1);
}

bool startsWith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int compare(const void *a, const void *b) {
    return *(const char *) a - *(const char *) b;
}

/**
 * Extracts and sorts alphabet letters.
 * E.g. for input cd&aab, result is: $abcd
 */
char *extractAlphabetLetters(char *input_chars) {
    bool letters[256] = {0};

    for (int i = 0; i < strlen(input_chars); ++i) {
        int index = input_chars[i];
        letters[index] = TRUE;
    }

    int alphabet_size = 0;
    for (int i = 0; i < 256; ++i) {
        if (letters[i] == TRUE) {
            ++alphabet_size;
        }
    }

    // finally collect letters
    char *alphabet = (char *) malloc(alphabet_size * sizeof(char));
    int index = 0;
    for (int i = 0; i < 256; ++i) {
        if (letters[i] == TRUE) {
            alphabet[index] = (char) i;
            ++index;
        }
    }

    alphabet[alphabet_size] = '\0';
    qsort(alphabet, strlen(alphabet), 1, compare);

    return alphabet;
}

/**
 * Gets the used alphabet in ascending order from given file
 */
void getAlphabetFromFile(const char *file_name, char **alphabet, char **input) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        error("Error while opening file.");
    }

    // calculate total file size
    fseek(file, 0L, SEEK_END);
    long int total_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *all_lines = (char *) malloc(total_size * sizeof(char));

    char line[1000];
    long int real_len = 0;
    while (fgets(line, sizeof(line), file)) {
        if (startsWith(">", strtok(line, "\n"))) {
            continue;
        }

        real_len += strlen(line);
        strcat(all_lines, line);
    }

    fclose(file);

    *input = (char *) malloc(real_len * sizeof(char));
    strcpy(*input, all_lines);

    // do reallocation to skip all new_lines
    all_lines = realloc(all_lines, real_len * sizeof(char));
    *alphabet = extractAlphabetLetters(all_lines);
}
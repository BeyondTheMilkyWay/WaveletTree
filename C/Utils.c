// Utils implementation.
// Created by dsisejkovic on 10.01.16..
//

#include "Utils.h"


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

void logln(char *msg) {
    printf("|%s\n", msg);
}

void error(const char *msg) {
    printf("|%s\n", msg);
    exit(-1);
}

bool compareStrings(char *str1, char *str2) {
    int len1 = (int) strlen(str1);
    int len2 = (int) strlen(str2);

    if (len1 != len2) {
        return FALSE;
    }

    for (int i = 0; i < len1; ++i) {
        if (str1[i] != str2[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

char *replaceSpaces(char *data) {
    int len = (int) strlen(data);

    for (int i = 0; i < len; ++i) {
        if (data[i] == ' ') {
            data[i] = '_';
        }
    }

    return data;
}

bool startsWith(const char *pre, const char *str) {
    return strncmp(pre, str, 1) == 0;
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
    char *alphabet = (char *) malloc((alphabet_size + 1) * sizeof(char));
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
void getAlphabetFromFile(const char *file_name, char **alphabet, char **input, int *input_len, int *alphabet_len) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        error("Error while opening file.");
    }

    // calculate total file size
    fseek(file, 0L, SEEK_END);
    long int total_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *all_lines = (char *) malloc((total_size + 1) * sizeof(char));
    fread(all_lines, (size_t) total_size, 1, file);
    all_lines[total_size] = '\0';

    int num_of_nl = 0;
    int first_nl_index = 0;

    //remove first line if starts with '>'
    if (startsWith(">", all_lines)) {
        // find index of first newline
        while (all_lines[first_nl_index++] != '\n');

        // remove first line
        for (int i = 0; i < total_size; ++i) {
            if (all_lines[i + first_nl_index] == '\n') {
                ++num_of_nl;
            }

            all_lines[i] = all_lines[i + first_nl_index];
        }
    }

    int new_size = (int) (total_size - first_nl_index - num_of_nl);
    char *final_input = (char *) malloc((new_size + 2) * sizeof(char));
    final_input[new_size] = '\0';


    // extract used alphabet
    // remove newlines and replace spaces
    bool letters[256] = {0};

    if (num_of_nl == 0) {
        strcpy(final_input, all_lines);
        for (int i = 0; i < new_size; ++i) {
            letters[final_input[i]] = TRUE;
        }
    } else {
        // remove all newlines
        for (int i = 0, j = 0; j < new_size; ++i) {
            if (all_lines[i] != '\n') {
                final_input[j] = all_lines[i];
                letters[final_input[j]] = TRUE;
                ++j;
            }
        }
    }

    replaceSpaces(final_input);
    final_input[new_size] = '$';
    final_input[new_size + 1] = '\0';
    *input_len = new_size + 1;

    free((void *) all_lines);
    fclose(file);

    int alphabet_size = 0;
    for (int i = 0; i < 256; ++i) {
        if (letters[i] == TRUE) {
            ++alphabet_size;
        }
    }

    // finally collect letters
    char *tmp_alphabet = (char *) malloc((alphabet_size + 2) * sizeof(char));
    int index = 0;
    for (int i = 0; i < 256; ++i) {
        if (letters[i] == TRUE) {
            tmp_alphabet[index] = (char) i;
            ++index;
        }
    }

    tmp_alphabet[alphabet_size] = '$';
    tmp_alphabet[alphabet_size + 1] = '\0';
    *alphabet_len = (int) strlen(tmp_alphabet);
    qsort(tmp_alphabet, (size_t) *alphabet_len, 1, compare);

    *input = final_input;
    *alphabet = tmp_alphabet;
}

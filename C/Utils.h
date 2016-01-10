//
// Created by dsisejkovic on 10.01.16..
//

#ifndef C_UTILS_H
#define C_UTILS_H

#include "Basic.h"

void error(const char *msg);

char *replaceSpaces(char *data);

bool compareStrings(char *str1, char *str2);

bool startsWith(const char *pre, const char *str);

int compare(const void *a, const void *b);

char *extractAlphabetLetters(char *input_chars);

void getAlphabetFromFile(const char *file_name, char **alphabet, char **input);

#endif //C_UTILS_H

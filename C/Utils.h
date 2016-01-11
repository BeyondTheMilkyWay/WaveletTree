//
// Created by dsisejkovic on 10.01.16..
//

#ifndef C_UTILS_H
#define C_UTILS_H

#include "Basic.h"

/**
 * Prints given error 'msg' and exists program.
 */
void error(const char *msg);

/**
 * Replaces all space characters with '_'.
 */
char *replaceSpaces(char *data);

/**
 * Basic character comparator.
 */
bool compareStrings(char *str1, char *str2);

/**
 * Checks if string 'str' starts with prefix 'pre'.
 */
bool startsWith(const char *pre, const char *str);

/**
 * Compares two characters. Used for sorting.
 */
int compare(const void *a, const void *b);

/**
 * Extracts alphabet letters from given input stream.
 */
char *extractAlphabetLetters(char *input_chars);

/**
 * Reads input file and extracts alphabet letters.
 */
void getAlphabetFromFile(const char *file_name, char **alphabet, char **input);

#endif //C_UTILS_H

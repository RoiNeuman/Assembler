#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdio.h>

#define READ_LINE_MAX 256
#define READING_ERROR 0
#define READING_EOF (-1)
#define LABEL_START_POSITION 0
#define LABEL_MAX_LENGTH 30
#define LABEL_WITHOUT_DECLARATION (-1)

/* Represent a boolean */
typedef enum Boolean {
    false,
    true
} Boolean;

/* Convert decimal number to binary number */
unsigned long decimalToBinary(int number);

/* Convert binary number to decimal number */
int binaryToDecimal(unsigned long number);

/* Convert binary number to positive decimal number */
unsigned int binaryToUnsignedDecimal(unsigned long number);

/*
 * Strings concatenation.
 * Return new char pointer array with the length of both strings and with their content one after the other.
*/
char *stringConcat(const char *str1, const char *str2);

/* Read a line from a file stream */
int readFileLine(char **line, FILE *fp, const char *fName);

/* Checking white character */
Boolean isWhiteCharacter(int c);

/* Checking white character or comma */
Boolean isWhiteCharOrComma(int c);

/* Checking if the given line is a comment line */
Boolean isComment(const char *line, int start);

/* Checking label content */
Boolean isLabel(const char *line, int start, int end);

/* Checking whether the given line contain a label */
Boolean isLineLabel(const char *line, int start, int end);

/* Checking whether the given line is a guidance line or instructive line */
Boolean isGuidanceLine(const char *line, int start);

/*
 * Return new string which is a part of the given string starting at the start index in the given length.
 * Return NULL if out of memory.
*/
char *substring(const char *string, int start, int length);

/*
 * Search for the first occurrence of character c in the given string str in the given range.
 * Return NULL if not found.
*/
char *strnchrRanged(const char *str, int c, int start, int end);

#endif
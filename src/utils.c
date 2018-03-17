#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "utils.h"
#include "memoryManager.h"
#include "errors.h"

/* Convert decimal number to binary number */
unsigned long decimalToBinary(int number)
{
    unsigned long binary;
    int i, absNum;

    binary = 0;
    i = 1;
    absNum = abs(number);

    while (absNum != 0) {
        binary += ((absNum % 2) * i);
        absNum /= 2;
        i *= 10;
    }

    /* Handling negative number using the two's complement method */
    if (number < 0) {
        binary = ~binary;
        binary++;
    }

    return binary;
}

/* Convert binary number to decimal number */
int binaryToDecimal(unsigned long number)
{
    int decimal, i, sign;

    decimal = 0;
    i = 1;
    sign = ((~(ULONG_MAX / 2)) & number) == 0 ? 1 : -1;

    /* Removing the number sign */
    number &= (ULONG_MAX / 2);

    while (number != 0) {
        decimal += ((number & 10) * i);
        number /= 10;
        i *= 2;
    }

    return (decimal * sign);
}

/* Convert binary number to positive decimal number */
unsigned int binaryToUnsignedDecimal(unsigned long number)
{
    unsigned int decimal, i;

    decimal = 0;
    i = 1;

    while (number != 0) {
        decimal += ((number & 10) * i);
        number /= 10;
        i *= 2;
    }

    return decimal;
}

/*
 * Strings concatenation.
 * Return new char pointer array with the length of both strings and with their content one after the other.
*/
char *stringConcat(const char *str1, const char *str2)
{
    const size_t len1 = strlen(str1);
    const size_t len2 = strlen(str2);
    char *concat;

    /* Allocating the two strings length +1 for \0 */
    concat = (char *)autoDispMalloc(sizeof(char) * (len1 + len2 + 1));
    if (concat == NULL) return NULL;

    strcpy(concat, str1);
    strcat(concat, str2);
    return concat;
}

/* Read a line from a file stream */
int readFileLine(char **line, FILE *fp, const char *fName)
{
    *line = (char *)autoDispMalloc(sizeof(char) * READ_LINE_MAX);
    if (*line == NULL) {
        logError(outOfMemory, "While reading a line from a file, readFileLine().");
        return READING_ERROR;
    }
    if (fgets(*line, READ_LINE_MAX, fp) == NULL) {
        if (ferror(fp)) {
            /* Error in reading from file */
            logError(readFromFileError, fName);
            return READING_ERROR;
        } else {
            /* Only EOF was read */
            return READING_EOF;
        }
    }
    return strlen(*line);
}

/* Checking white character */
Boolean isWhiteCharacter(const int c)
{
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n') ? true : false;
}

/* Checking white character or comma */
Boolean isWhiteCharOrComma(const int c)
{
    return (c == ',' || c == ' ' || c == '\t' || c == '\r' || c == '\n') ? true : false;
}

/* Checking if the given line is a comment line */
Boolean isComment(const char *line, int start)
{
    return *(line + start) == ';' ? true : false;
}

/* Checking label content */
Boolean isLabel(const char *line, int start, int end)
{
    Boolean _isLabel;
    _isLabel = true;
    if (!isalpha(*(line + start))) {
        _isLabel = false;
    }
    if (end - start >= LABEL_MAX_LENGTH) {
        logError(labelMaxLength, NULL);
        _isLabel = false;
    }
    return _isLabel;
}

/* Checking whether the given line contain a label */
Boolean isLineLabel(const char *line, int start, int end)
{
    Boolean _isLabel;
    _isLabel = false;
    if (*(line + end) != ':' && isLabel(line, start, end)) {
        _isLabel = true;
        if (!isalpha(*(line + start))) {
            logError(labelFirstChar, NULL);
            _isLabel = false;
        }
        if (start != LABEL_START_POSITION) {
            logError(labelStartPosition, NULL);
            _isLabel = false;
        }
    }
    return _isLabel;
}

/* Checking whether the given line is a guidance line or instructive line */
Boolean isGuidanceLine(const char *line, int start)
{
    return *(line + start) == '.' ? true : false;
}

/*
 * Return new string which is a part of the given string starting at the start index in the given length.
 * Return NULL if out of memory.
*/
char *substring(const char *string, int start, int length)
{
    int i;
    char *str;

    /* Allocating length + 1 characters, extra 1 for the terminating character */
    str = (char *)autoDispMalloc(sizeof(char) * (length + 1));

    if (str == NULL) {
        return NULL;
    }

    for (i = start; i < length && i < strlen(string); ++i) {
        str[i - start] = string[i];
    }

    /* Adding the string terminating character */
    str[length] = '\0';

    return str;
}

/*
 * Search for the first occurrence of character c in the given string str in the given range.
 * Return NULL if not found.
*/
char *strnchrRanged(const char *str, const int c, const int start, const int end)
{
    int i;

    for (i = start; i <= end && i < strlen(str) && *(str + i) != '\0'; ++i) {
        if (*(str + i) == c) {
            /* The first occurrence of c in str between the range of start and end */
            return (char *)(str + i);
        }
    }

    /* c was not found */
    return NULL;
}
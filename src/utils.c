#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "memoryManager.h"
#include "errors.h"

/* Convert decimal number to binary number */
int decimalToBinary(int number)
{
    int binary = 0, i = 1;

    while (number != 0) {
        binary += ((number % 2) * i);
        number /= 2;
        i *= 10;
    }
    return binary;
}

/* Convert binary number to decimal number */
int binaryToDecimal(int number)
{
    int decimal = 0, i = 1;

    while (number != 0) {
        decimal += ((number & 10) * i);
        number /= 10;
        i *= 2;
    }
    return decimal;
}

/* Convert mozar number to binary number */
int mozarToBinary(char *number)
{
    return 0;
}

/* Convert binary number to mozar number */
char *binaryToMozar(int number)
{
    return NULL;
}

/* Strings concatenation */
/* Return new char pointer array with the length of both strings and with their content one after the other */
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
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == EOF) ? true : false;
}

/* Checking white character or comma */
Boolean isWhiteCharOrComma(const int c)
{
    return (c == ',' || c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == EOF) ? true : false;
}

/* Checking if the given line is a comment line */
Boolean isComment(const char *line, int start)
{
    return *(line + start) == ';' ? true : false;
}

/* Checking whether the given line contain a label */
Boolean isLabel(const char *line, int end)
{
    return *(line + end) == ':' ? true : false;
}

/* Checking whether the given line is a guidance line or instructive line */
Boolean isGuidanceLine(const char *line, int start)
{
    return *(line + start) == '.' ? true : false;
}
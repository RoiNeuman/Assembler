#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#define READ_LINE_MAX 256
#define READING_ERROR 0
#define READING_EOF (-1)

/* Represent a boolean */
typedef enum Boolean {
    false,
    true
} Boolean;

/* Convert decimal number to binary number */
int decimalToBinary(int number);

/* Convert binary number to decimal number */
int binaryToDecimal(int number);

/* Convert mozar number to binary number */
int mozarToBinary(char *number);

/* Convert binary number to mozar number */
char *binaryToMozar(int number);

/* Strings concatenation */
/* Return new char pointer array with the length of both strings and with their content one after the other */
char *stringConcat(const char *str1, const char *str2);

/* Read a line from a file stream */
int readFileLine(char **line, FILE *fp, const char *fName);

/* Checking white character */
Boolean isWhiteCharacter(int c);

/* Checking if the given line is a comment line */
Boolean isComment(const char *line, int start);

#endif
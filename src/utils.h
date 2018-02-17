#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

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
/* return new char pointer array with the length of both strings and with their content one after the other */
char *stringConcat(const char *str1, const char *str2);

#endif
#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

/* Represent a boolean */
typedef enum Boolean {
    false,
    true
} Boolean;

typedef char *String;

/* Convert decimal number to binary number */
int decimalToBinary(int number);

/* Convert binary number to decimal number */
int binaryToDecimal(int number);

/* Convert mozar number to binary number */
int mozarToBinary(String number);

/* Convert binary number to mozar number */
String binaryToMozar(int number);

/* Strings concatenation */
String stringConcat(String str1, String str2);

#endif
#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

/* Convert decimal number to binary number */
int decimalToBinary(int number);

/* Convert binary number to decimal number */
int binaryToDecimal(int number);

/* Convert mozar number to binary number */
int mozarToBinary(char *number);

/* Convert binary number to mozar number */
char *binaryToMozar(int number);

#endif
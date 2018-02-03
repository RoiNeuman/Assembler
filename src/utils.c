#include "utils.h"

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

}

/* Convert binary number to mozar number */
char *binaryToMozar(int number)
{

}
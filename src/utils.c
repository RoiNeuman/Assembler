#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "memoryManager.h"

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
/* return new char pointer array with the length of both strings and with their content one after the other */
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
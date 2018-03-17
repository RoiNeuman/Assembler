#include "mozarUtils.h"
#include "utils.h"
#include "errors.h"
#include "memoryManager.h"
#include "resultFilesHandler.h"

/* Convert binary number to mozar number */
char *binaryToMozar(unsigned long number)
{
    char *mozar;
    int digitsCounter;
    unsigned int digit;
    unsigned long temp;

    digitsCounter = 0;
    temp = number;
    while (temp != 0) {
        temp = temp>>MOZAR_IN_BINARY_LENGTH;
        digitsCounter++;
    }

    mozar = (char *)autoDispMalloc(sizeof(char) * digitsCounter + TERMINATE_STRING_LENGTH);

    if (mozar == NULL) {
        logError(outOfMemory, "Binary to mozar.");
        return NULL;
    }

    while (digitsCounter != 0) {
        digitsCounter--;
        digit = number & DECIMAL_MOZAR_MAX;
        number = number>>MOZAR_IN_BINARY_LENGTH;
        *(mozar + digitsCounter) = decimalToMozar(binaryToUnsignedDecimal(digit));
    }

    /* Adding terminating character */
    *(mozar + digitsCounter) = '\0';

    return mozar;
}

/* Return a Mozar digit */
char decimalToMozar(unsigned int number)
{
    switch (number) {
        case 0:
            return MOZAR_0;
        case 1:
            return MOZAR_1;
        case 2:
            return MOZAR_2;
        case 3:
            return MOZAR_3;
        case 4:
            return MOZAR_4;
        case 5:
            return MOZAR_5;
        case 6:
            return MOZAR_6;
        case 7:
            return MOZAR_7;
        case 8:
            return MOZAR_8;
        case 9:
            return MOZAR_9;
        case 10:
            return MOZAR_10;
        case 11:
            return MOZAR_11;
        case 12:
            return MOZAR_12;
        case 13:
            return MOZAR_13;
        case 14:
            return MOZAR_14;
        case 15:
            return MOZAR_15;
        case 16:
            return MOZAR_16;
        case 17:
            return MOZAR_17;
        case 18:
            return MOZAR_18;
        case 19:
            return MOZAR_19;
        case 20:
            return MOZAR_20;
        case 21:
            return MOZAR_21;
        case 22:
            return MOZAR_22;
        case 23:
            return MOZAR_23;
        case 24:
            return MOZAR_24;
        case 25:
            return MOZAR_25;
        case 26:
            return MOZAR_26;
        case 27:
            return MOZAR_27;
        case 28:
            return MOZAR_28;
        case 29:
            return MOZAR_29;
        case 30:
            return MOZAR_30;
        case 31:
            return MOZAR_31;
        default:
            return MOZAR_0;
    }
}
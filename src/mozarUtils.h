#ifndef ASSEMBLER_MOZARUTILS_H
#define ASSEMBLER_MOZARUTILS_H

#define WORD_IN_MOZAR_LENGTH 2
#define ADDRESS_IN_MOZAR_LENGTH 2
#define DECIMAL_MOZAR_MAX 31
#define MOZAR_IN_BINARY_LENGTH 100000

#define MOZAR_0 '!'
#define MOZAR_1 '@'
#define MOZAR_2 '#'
#define MOZAR_3 '$'
#define MOZAR_4 '%'
#define MOZAR_5 '^'
#define MOZAR_6 '&'
#define MOZAR_7 '*'
#define MOZAR_8 '<'
#define MOZAR_9 '>'
#define MOZAR_10 'a'
#define MOZAR_11 'b'
#define MOZAR_12 'c'
#define MOZAR_13 'd'
#define MOZAR_14 'e'
#define MOZAR_15 'f'
#define MOZAR_16 'g'
#define MOZAR_17 'h'
#define MOZAR_18 'i'
#define MOZAR_19 'j'
#define MOZAR_20 'k'
#define MOZAR_21 'l'
#define MOZAR_22 'm'
#define MOZAR_23 'n'
#define MOZAR_24 'o'
#define MOZAR_25 'p'
#define MOZAR_26 'q'
#define MOZAR_27 'r'
#define MOZAR_28 's'
#define MOZAR_29 't'
#define MOZAR_30 'u'
#define MOZAR_31 'v'

#include "utils.h"

/* Convert binary number to mozar number */
char *binaryToMozar(unsigned long number, Boolean isTwo);

/* Return a Mozar digit */
char decimalToMozar(unsigned int number);

#endif

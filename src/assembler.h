#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include "utils.h"

/* Operation code */
typedef enum Opcode {
    mov, /* Copy one operand to another */
    cmp, /* Compare two operands */
    add, /* Add two operands */
    sub, /* Subtract two operands */
    not, /* Revers the operand's bits */
    clr, /* Clear the operand's content */
    lea, /* Load the pointer of the first operand to the second operand */
    inc, /* Increase the operand's value by 1  */
    dec, /* Decrease the operand's value by 1 */
    jmp, /* Jump to Line (operand) */
    bne, /* Branch to Line (operand) if not equal (to zero, check the flag Z in register PSW) */
    red, /* Read char from the standard input */
    prn, /* Print char to the standard output */
    jsr, /* Jump to subroutine (function) */
    rts, /* Return from subroutine */
    stop /* Stop the program */
} Opcode;

typedef enum Utype {
    ival, /* Int value */
    cval /* Char value */
} Utype;

typedef struct Instruction {
    Opcode oc;
    struct Instruction *next;
} Instruction;

typedef struct Data {
    Utype utype;
    union u {
        int ival;
        char cval;
    };
    struct Data *next;
} Data;

typedef struct Label {
    char *name;
    int counter;
    Boolean hasEntry;
    struct Label *next;
} Label;

/* Parsed assembly file */
typedef struct ParsedFile {
    char *fName;
    int IC; /* Instruction counter */
    int DC; /* Data counter */
    Instruction *iList; /* Instructions list */
    Data *dList; /* Data list */
    Label *lList; /* Labels list */
    Boolean hasError;
} ParsedFile;

/* Run the assembler on a file */
void runAssemblerOnFile(char *fName);

/* Initializing new ParsedFile struct */
ParsedFile *initializeParsedFile(char *fName);

/* Add data to the data list */
Boolean addData(ParsedFile *pfp, int data);

#endif

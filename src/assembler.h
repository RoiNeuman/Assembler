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

/* An instruction line */
typedef struct Instruction {
    Opcode oc; /* Opcode of the instruction */
    struct Instruction *next; /* Next instruction on the list */
} Instruction;

/* A data line */
typedef struct Data {
    int value; /* The value of this data */
    struct Data *next; /* Next data on the list */
} Data;

/* Label counter's type */
typedef enum CounterType {
    IC, /* Instruction lines counter */
    DC /* Data lines counter */
} CounterType;

typedef struct LineCounter {
    int counter; /* The line position */
    CounterType ct; /* Line counter's type */
    struct LineCounter *next; /* The next line on the list */
} LineCounter;

/* A label */
typedef struct Label {
    char *name; /* The label's name */
    int counter; /* The label position */
    CounterType ct; /* Label counter's type */
    Boolean hasEntry; /* Is this label has an entry line */
    Boolean hasExtern; /* Is this label has an extern line */
    LineCounter *lines; /* Line with this label */
    struct Label *next; /* Next label on the list */
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

/* Add label to the labels list */
Boolean addLabel(ParsedFile *pfp, const char *line, int start, int end, CounterType ct, Boolean hasEntry, Boolean hasExtern);

/* Add new line counter to a label */
Boolean addLineCounter(ParsedFile *pfp, Label *label, CounterType ct);

#endif

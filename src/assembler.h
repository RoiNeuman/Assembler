#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include "utils.h"

#define IC_INSTRUCTION 1
#define IC_OPERAND 1
#define NOT_LINE_LABEL -1

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

/* Types of operands */
typedef enum OperandType {
    immediateAddressing, /* Contain the operand itself */
    directAddressing, /* A label to the operand */
    structAddressing, /* The operand is a property of a struct */
    registerAddressing /* The operand is a register */
} OperandType;

/* An operand of instruction */
typedef struct Operand {
    OperandType type; /* The type of the operand */
    int iData; /* The number part of the operand */
    char *strData; /* The string part of the operand */
} Operand;

/* Types of instructions */
typedef enum InstructionType {
    noOperands, /* Instruction with no operands */
    singleOperand, /* Instruction with single operand */
    twoOperands /* Instruction with two operands */
} InstructionType;

/* An instruction line */
typedef struct Instruction {
    Opcode oc; /* Opcode of the instruction */
    InstructionType instructionType; /* The instruction type */
    Operand *source; /* Source operands of this instruction */
    Operand *destination; /* Destination operands with of instruction */
    int line; /* The line in the source file */
    struct Instruction *next; /* Next instruction on the list */
} Instruction;

/* A data line */
typedef struct Data {
    int value; /* The value of this data */
    int line; /* The line in the source file */
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

/* Add line label to the labels list */
Boolean addLineLabel(ParsedFile *pfp, const char *line, int start, int end, CounterType ct, Boolean hasEntry, Boolean hasExtern, int lineCounter);

/* Add label to the labels list */
Boolean addLabel(ParsedFile *pfp, const char *line, int start, int end, CounterType ct, Boolean hasEntry, Boolean hasExtern);

/* Add new line counter to a label */
Boolean addLineCounter(ParsedFile *pfp, Label *label, CounterType ct, int lineCounter);

/* Add new no operands instruction to the instructions list */
Boolean addNoOperandsInstruction(ParsedFile *pfp, Opcode op);

/* Create new operand struct with initial values */
Boolean createOperand(Operand **ppOperand, OperandType operandType, int iData, char *strData);

/* Add new instruction with only one operand to the instruction list */
Boolean addSingleOperandInstruction(ParsedFile *pfp, Opcode op, Operand *pDestination);

/* Add new instruction with two operands to the instruction list */
Boolean addTwoOperandInstruction(ParsedFile *pfp, Opcode op, Operand *pSource, Operand *pDestination);

/* Set the source file line to a given number */
void setSourceFileLine(int number);

#endif
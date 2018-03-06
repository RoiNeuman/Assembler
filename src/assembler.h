#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include "errors.h"

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

/* Parsed file type */
typedef  struct ParsedFile {
    char *fName;

} ParsedFile;

/* Run the assembler on a file */
void runAssemblerOnFile(char *fName);

#endif

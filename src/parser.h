#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <stdio.h>
#include "assembler.h"

#define FIRST_INDEX 0
#define GUIDANCE_DATA ".data"
#define GUIDANCE_STRUCT ".struct"
#define GUIDANCE_STRING ".string"
#define GUIDANCE_ENTRY ".entry"
#define GUIDANCE_EXTERN ".extern"

#define INSTRUCTION_MOV "mov"
#define INSTRUCTION_CMP "cmp"
#define INSTRUCTION_ADD "add"
#define INSTRUCTION_SUB "sub"
#define INSTRUCTION_NOT "not"
#define INSTRUCTION_CLR "clr"
#define INSTRUCTION_LEA "lea"
#define INSTRUCTION_INC "inc"
#define INSTRUCTION_DEC "dec"
#define INSTRUCTION_JMP "jmp"
#define INSTRUCTION_BNE "bne"
#define INSTRUCTION_RED "red"
#define INSTRUCTION_PRN "prn"
#define INSTRUCTION_JSR "jsr"
#define INSTRUCTION_RTS "rts"
#define INSTRUCTION_STOP "stop"

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName);

/* Return the next index in the line which is not a white character */
int clearWhiteCharacters(const char *line, int length, int index);

/* Return the next index in the line which is not a white character or comma */
int clearWhiteCharOrComma(const char *line, const int length, int index);

/* Read the next word from a line */
/* Return the next index after the word */
int readNextWord(const char *line, int index, int *start, int *end);

#endif
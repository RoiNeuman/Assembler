#ifndef ASSEMBLER_INSTRUCTIONLINE_H
#define ASSEMBLER_INSTRUCTIONLINE_H

#include "assembler.h"
#include "utils.h"

/* Analyze two operands instruction line */
Boolean twoOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name);

/* Analyze single operand instruction line */
Boolean singleOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name);

/* Analyze no operands instruction line */
Boolean noOperandsInstruction(ParsedFile *pfp, Opcode op);

#endif
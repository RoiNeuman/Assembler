#ifndef ASSEMBLER_INSTRUCTIONLINE_H
#define ASSEMBLER_INSTRUCTIONLINE_H

#include "assembler.h"
#include "utils.h"

Boolean twoOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode oc);

Boolean singleOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode oc);

Boolean zeroOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode oc);

#endif
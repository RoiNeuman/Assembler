#include "instructionLine.h"
#include "parser.h"
#include "errors.h"

/* Analyze two operands instruction line */
Boolean twoOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name)
{
    Boolean hasError;

    hasError = false;


    return hasError;
}

/* Analyze single operand instruction line */
Boolean singleOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name)
{
    Boolean hasError;
    int startOfWord, endOfWord;
    Operand *operand;

    hasError = false;
    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    /* Checking for missing operand */
    if (endOfWord - startOfWord == 0) {
        logError(missOperand, name);
        hasError = true;
    }

    /* Analysing operand */
    if (hasError == false) {
        hasError = analyzeOperand(op, line, startOfWord, endOfWord, &operand);
    }

    /* Adding instruction */
    if (hasError == false) {
        hasError = addSingleOperandInstruction(pfp, op, operand);
    }

    return hasError;
}

/* Analyze no operands instruction line */
Boolean noOperandsInstruction(ParsedFile *pfp, Opcode op)
{
    return addNoOperandsInstruction(pfp, op);
}
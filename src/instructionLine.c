#include <ctype.h>
#include "instructionLine.h"
#include "memoryManager.h"
#include "parser.h"
#include "errors.h"

Boolean analyzeSourceOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeDestinationOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeFourAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeThreeAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeTwoAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeImmediateAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeDirectAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeStructAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);
Boolean analyzeRegisterAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand);

/* Analyze two operands instruction line */
Boolean twoOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name)
{
    Boolean hasError;
    int startOfWord, endOfWord;
    Operand *sourceOperand, *destinationOperand;

    hasError = false;
    sourceOperand = NULL;
    destinationOperand = NULL;

    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    lineIndex = readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    /* Checking for missing source operand */
    if (endOfWord - startOfWord == 0) {
        logError(missSourceOperand, name);
        pfp->hasError = true;
        return hasError;
    }

    /* Analysing source operand */
    hasError = analyzeSourceOperand(pfp, op, line, startOfWord, endOfWord, &sourceOperand);

    if (sourceOperand == NULL) {
        logError(undefinedSourceOperand, name);
        pfp->hasError = true;
    }

    if (hasError == false) {
        lineIndex = clearWhiteCharOrComma(line, length, lineIndex);
        readNextWord(line, lineIndex, &startOfWord, &endOfWord);

        /* Checking for missing destination operand */
        if (endOfWord - startOfWord == 0) {
            logError(missDestinationOperand, name);
            pfp->hasError = true;
            return hasError;
        }

        /* Analysing destination operand */
        hasError = analyzeDestinationOperand(pfp, op, line, startOfWord, endOfWord, &destinationOperand);

        if (destinationOperand == NULL) {
            logError(undefinedDestinationOperand, name);
            pfp->hasError = true;
        }
    }

    /* Adding instruction */
    if (hasError == false && sourceOperand != NULL && destinationOperand != NULL) {
        hasError = addTwoOperandInstruction(pfp, op, sourceOperand, destinationOperand);
    }

    return hasError;
}

/* Analyze single operand instruction line */
Boolean singleOperandInstruction(ParsedFile *pfp, const char *line, int length, int lineIndex, Opcode op, const char *name)
{
    Boolean hasError;
    int startOfWord, endOfWord;
    Operand *operand;

    hasError = false;
    operand = NULL;

    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    /* Checking for missing operand */
    if (endOfWord - startOfWord == 0) {
        logError(missDestinationOperand, name);
        pfp->hasError = true;
        return hasError;
    }

    /* Analysing operand */
    hasError = analyzeDestinationOperand(pfp, op, line, startOfWord, endOfWord, &operand);

    /* Adding instruction */
    if (hasError == false && operand != NULL) {
        hasError = addSingleOperandInstruction(pfp, op, operand);
    } else if (hasError == false && operand == NULL) {
        logError(undefinedDestinationOperand, name);
        pfp->hasError = true;
    }

    return hasError;
}

/* Analyze no operands instruction line */
Boolean noOperandsInstruction(ParsedFile *pfp, Opcode op)
{
    return addNoOperandsInstruction(pfp, op);
}

/* Analyze a source operand */
Boolean analyzeSourceOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = false;

    /* Filter possible operands' types for each opcode */
    switch (op) {
        case mov:
        case cmp:
        case add:
        case sub:
            hasError = analyzeFourAddressTypeOperand(pfp, line, startOfWord, endOfWord, ppOperand);
            break;
        case lea:
            hasError = analyzeTwoAddressTypeOperand(pfp, line, startOfWord, endOfWord, ppOperand);
            break;
        default:
            pfp->hasError = true;
    }

    return hasError;
}

/* Analyze a destination operand */
Boolean analyzeDestinationOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = false;

    /* Filter possible operands' types for each opcode */
    switch (op) {
        case mov:
        case add:
        case sub:
        case not:
        case clr:
        case lea:
        case inc:
        case dec:
        case jmp:
        case bne:
        case red:
        case jsr:
            hasError = analyzeThreeAddressTypeOperand(pfp, line, startOfWord, endOfWord, ppOperand);
            break;
        case cmp:
        case prn:
            hasError = analyzeFourAddressTypeOperand(pfp, line, startOfWord, endOfWord, ppOperand);
            break;
        default:
            pfp->hasError = true;
    }

    return hasError;
}

/* Analyze an instruction with four types of addressing */
Boolean analyzeFourAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand
**ppOperand)
{
    Boolean hasError;

    hasError = analyzeImmediateAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeDirectAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeStructAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeRegisterAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    return hasError;
}

/* Analyze an instruction with three types of addressing */
Boolean analyzeThreeAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = analyzeDirectAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeStructAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeRegisterAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    return hasError;
}

/* Analyze an instruction with two types of addressing */
Boolean analyzeTwoAddressTypeOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = analyzeDirectAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);

    if (hasError == false && *ppOperand == NULL) {
        hasError = analyzeStructAddressingOperand(pfp, line, startOfWord, endOfWord, ppOperand);
    }

    return hasError;
}

/* Analyze an immediate addressing operand */
Boolean analyzeImmediateAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    int sign, c, index, number;
    Boolean hasError;

    sign = 1;
    number = 0;
    hasError = false;

    if (*(line + startOfWord) == '#') {
        if (endOfWord - startOfWord == 1) {
            logError(illegalImmediateAddressingOperand, NULL);
            pfp->hasError = true;
            return false;
        }
        if ((c = *(line + startOfWord + 1)) == '+' || c == '-') {
            /* Recording sign */
            sign = (c == '-' ? -1 : 1);
            index = startOfWord + 2;
        } else {
            index = startOfWord + 1;
        }
        while (index <= endOfWord) {
            if (isdigit(c = *(line + index))) {
                number = ((number * 10) + (c - '0'));
            } else {
                logError(illegalImmediateAddressingOperand, NULL);
                pfp->hasError = true;
                return false;
            }
            index++;
        }

        /* Creating the new operand */
        hasError = createOperand(ppOperand, immediateAddressing, (number * sign), NULL);
    }

    return hasError;
}

/* Analyze a direct addressing operand */
Boolean analyzeDirectAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

/* Analyze a struct addressing operand */
Boolean analyzeStructAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

/* Analyze a register addressing operand */
Boolean analyzeRegisterAddressingOperand(ParsedFile *pfp, const char *line, int startOfWord, int endOfWord, Operand **ppOperand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}
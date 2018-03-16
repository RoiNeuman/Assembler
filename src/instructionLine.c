#include "instructionLine.h"
#include "parser.h"
#include "errors.h"

Boolean analyzeSourceOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeDestinationOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeFourAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeThreeAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeTwoAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeImmediateAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeDirectAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeStructAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);
Boolean analyzeRegisterAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand);

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
Boolean analyzeSourceOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = false;

    /* Filter possible operands' types for each opcode */
    switch (op) {
        case mov:
        case cmp:
        case add:
        case sub:
            hasError = analyzeFourAddressTypeOperand(line, startOfWord, endOfWord, operand);
            break;
        case lea:
            hasError = analyzeTwoAddressTypeOperand(line, startOfWord, endOfWord, operand);
            break;
        default:
            pfp->hasError = true;
    }

    return hasError;
}

/* Analyze a destination operand */
Boolean analyzeDestinationOperand(ParsedFile *pfp, Opcode op, const char *line, int startOfWord, int endOfWord, Operand **operand)
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
            hasError = analyzeThreeAddressTypeOperand(line, startOfWord, endOfWord, operand);
            break;
        case cmp:
        case prn:
            hasError = analyzeFourAddressTypeOperand(line, startOfWord, endOfWord, operand);
            break;
        default:
            pfp->hasError = true;
    }

    return hasError;
}

/* Analyze an instruction with four types of addressing */
Boolean analyzeFourAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = analyzeImmediateAddressingOperand(line, startOfWord, endOfWord, operand);

    if (hasError == false && *operand == NULL) {
        hasError = analyzeDirectAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    if (hasError == false && *operand == NULL) {
        hasError = analyzeStructAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    if (hasError == false && *operand == NULL) {
        hasError = analyzeRegisterAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    return hasError;
}

/* Analyze an instruction with three types of addressing */
Boolean analyzeThreeAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = analyzeDirectAddressingOperand(line, startOfWord, endOfWord, operand);

    if (hasError == false && *operand == NULL) {
        hasError = analyzeStructAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    if (hasError == false && *operand == NULL) {
        hasError = analyzeRegisterAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    return hasError;
}

/* Analyze an instruction with two types of addressing */
Boolean analyzeTwoAddressTypeOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = analyzeDirectAddressingOperand(line, startOfWord, endOfWord, operand);

    if (hasError == false && *operand == NULL) {
        hasError = analyzeStructAddressingOperand(line, startOfWord, endOfWord, operand);
    }

    return hasError;
}

/* Analyze an immediate addressing operand */
Boolean analyzeImmediateAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

/* Analyze a direct addressing operand */
Boolean analyzeDirectAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

/* Analyze a struct addressing operand */
Boolean analyzeStructAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

/* Analyze a register addressing operand */
Boolean analyzeRegisterAddressingOperand(const char *line, int startOfWord, int endOfWord, Operand **operand)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}
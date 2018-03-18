#include <string.h>
#include "lineAnalyzer.h"
#include "dataLine.h"
#include "instructionLine.h"
#include "errors.h"

Boolean analyzeGuidanceLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, Boolean *hasLabel);
Boolean analyzeInstructionLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord);

/* Analyze the given line */
Boolean analyzeLine(ParsedFile *pfp, const char *line, const int length)
{
    int lineIndex, startOfWord, endOfWord, startOfLabel, endOfLabel, lineCounter;
    Boolean hasLabel, hasError;
    CounterType ct;

    startOfLabel = 0;
    endOfLabel = 0;
    lineIndex = clearWhiteCharacters(line, length, FIRST_INDEX);

    /* Skipping empty line */
    if (lineIndex == length) {
        return false;
    }

    lineIndex = readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    /* Skipping comment line */
    if (isComment(line, startOfWord)) {
        return false;
    }

    /* Marking label if any */
    if ((hasLabel = isLineLabel(line, startOfWord, endOfWord))) {
        startOfLabel = startOfWord;
        endOfLabel = endOfWord - 1;
        lineIndex = clearWhiteCharacters(line, length, endOfWord + 1);
        lineIndex = readNextWord(line, lineIndex, &startOfWord, &endOfWord);
    }

    /* Checking what is the line's type */
    if (isGuidanceLine(line, startOfWord)) {
        /* Guidance line (data line) */
        ct = DC;
        lineCounter = pfp->DC;
        hasError = analyzeGuidanceLine(pfp, line, length, lineIndex, startOfWord, &hasLabel);
    } else {
        /* Instruction line */
        ct = IC;
        lineCounter = pfp->IC;

        /* Incrementing the instructions counter */
        pfp->IC = pfp->IC + IC_INSTRUCTION;

        hasError = analyzeInstructionLine(pfp, line, length, lineIndex, startOfWord);
    }

    /* Adding the label to the parsed file struct */
    if (hasError == false && hasLabel) {
        hasError = addLineLabel(pfp, line, startOfLabel, endOfLabel, ct, false, false, lineCounter);
    }

    return hasError;
}

/* Analyze a guidance line */
Boolean analyzeGuidanceLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, Boolean *hasLabel)
{
    Boolean hasError;

    hasError = false;

    if (0 == strncmp(line + startOfWord, GUIDANCE_DATA, strlen(GUIDANCE_DATA))) {
        /* Data line */
        hasError = analyzeDataLine(pfp, line, length, lineIndex);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_STRUCT, strlen(GUIDANCE_STRUCT))) {
        /* Struct line */
        hasError = analyzeStructLine(pfp, line, length, lineIndex);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_STRING, strlen(GUIDANCE_STRING))) {
        /* String line */
        hasError = analyzeStringLine(pfp, line, length, lineIndex);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_ENTRY, strlen(GUIDANCE_ENTRY))) {
        /* Entry line */
        if (*hasLabel) {
            logError(labelWithEntry, NULL);
            *hasLabel = false;
        }
        hasError = analyzeEntryLine(pfp, line, length, lineIndex);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_EXTERN, strlen(GUIDANCE_EXTERN))) {
        /* Extern line */
        if (*hasLabel) {
            logError(labelWithExtern, NULL);
            *hasLabel = false;
        }
        hasError = analyzeExternLine(pfp, line, length, lineIndex);
    }
    return hasError;
}

/* Analyze an instruction line */
Boolean analyzeInstructionLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord)
{
    Boolean hasError;

    hasError = false;

    if (0 == strncmp(line + startOfWord, INSTRUCTION_MOV, strlen(INSTRUCTION_MOV))) {
        /* MOVe instruction */
        hasError = twoOperandInstruction(pfp, line, length, lineIndex, mov, INSTRUCTION_MOV);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_CMP, strlen(INSTRUCTION_CMP))) {
        /* CoMPare instruction */
        hasError = twoOperandInstruction(pfp, line, length, lineIndex, cmp, INSTRUCTION_CMP);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_ADD, strlen(INSTRUCTION_ADD))) {
        /* ADD instruction */
        hasError = twoOperandInstruction(pfp, line, length, lineIndex, add, INSTRUCTION_ADD);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_SUB, strlen(INSTRUCTION_SUB))) {
        /* SUBtract instruction */
        hasError = twoOperandInstruction(pfp, line, length, lineIndex, sub, INSTRUCTION_SUB);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_NOT, strlen(INSTRUCTION_NOT))) {
        /* NOT instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, not, INSTRUCTION_NOT);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_CLR, strlen(INSTRUCTION_CLR))) {
        /* CLeaR instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, clr, INSTRUCTION_CLR);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_LEA, strlen(INSTRUCTION_LEA))) {
        /* Load Effective Address */
        hasError = twoOperandInstruction(pfp, line, length, lineIndex, lea, INSTRUCTION_LEA);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_INC, strlen(INSTRUCTION_INC))) {
        /* INCrease instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, inc, INSTRUCTION_INC);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_DEC, strlen(INSTRUCTION_DEC))) {
        /* DECrease instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, dec, INSTRUCTION_DEC);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_JMP, strlen(INSTRUCTION_JMP))) {
        /* Jump instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, jmp, INSTRUCTION_JMP);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_BNE, strlen(INSTRUCTION_BNE))) {
        /* Branch if Not Equal instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, bne, INSTRUCTION_BNE);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_RED, strlen(INSTRUCTION_RED))) {
        /* REeD instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, red, INSTRUCTION_RED);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_PRN, strlen(INSTRUCTION_PRN))) {
        /* PRiNt instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, prn, INSTRUCTION_PRN);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_JSR, strlen(INSTRUCTION_JSR))) {
        /* Jump to SubRoutine instruction */
        hasError = singleOperandInstruction(pfp, line, length, lineIndex, jsr, INSTRUCTION_JSR);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_RTS, strlen(INSTRUCTION_RTS))) {
        /* ReTurn from Subroutine instruction */
        hasError = noOperandsInstruction(pfp, rts);
    } else if (0 == strncmp(line + startOfWord, INSTRUCTION_STOP, strlen(INSTRUCTION_STOP))) {
        /* STOP instruction */
        hasError = noOperandsInstruction(pfp, stop);
    } else {
        logError(undefinedInstruction, NULL);
        pfp->hasError = true;
    }

    return hasError;
}
#include <string.h>
#include "lineAnalyzer.h"
#include "dataLine.h"
#include "errors.h"

Boolean analyzeGuidanceLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord, Boolean *hasLabel);
Boolean analyzeInstructionLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);

/* Analyze the given line */
Boolean analyzeLine(ParsedFile *pfp, const char *line, const int length)
{
    int lineIndex, startOfWord, endOfWord, startOfLabel = 0, endOfLabel = 0;
    Boolean hasLabel, hasError;
    CounterType ct;

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
        hasError = analyzeGuidanceLine(pfp, line, length, lineIndex, startOfWord, endOfWord, &hasLabel);
    } else {
        /* Instruction line */
        ct = IC;
        hasError = analyzeInstructionLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    }

    /* Adding the label to the parsed file struct */
    if (hasError == false && hasLabel) {
        hasError = addLabel(pfp, line, startOfLabel, endOfLabel, ct, false, false);
    }

    return hasError;
}

/* Analyze a guidance line */
Boolean analyzeGuidanceLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord, Boolean *hasLabel)
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
        hasError = analyzeEntryLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_EXTERN, strlen(GUIDANCE_EXTERN))) {
        /* Extern line */
        if (*hasLabel) {
            logError(labelWithExtern, NULL);
            *hasLabel = false;
        }
        hasError = analyzeExternLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    }
    return hasError;
}

/* Analyze an instruction line */
Boolean analyzeInstructionLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}
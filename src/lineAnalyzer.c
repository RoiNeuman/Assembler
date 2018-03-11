#include <string.h>
#include <ctype.h>
#include "lineAnalyzer.h"
#include "errors.h"

static Boolean _analyzeGuidanceLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int
endOfWord, Boolean *hasLabel);
static Boolean _analyzeInstructionLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);
static Boolean _analyzeDataLine(ParsedFile *pfp, const char *line, int length, int lineIndex);
static Boolean _analyzeStructLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);
static Boolean _analyzeStringLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);
static Boolean _analyzeEntryLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);
static Boolean _analyzeExternLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);

/* Analyze the given line */
Boolean analyzeLine(ParsedFile *pfp, const char *line, const int length)
{
    int lineIndex, startOfWord, endOfWord, startOfLabel = 0, endOfLabel = 0;
    Boolean hasLabel, hasError;

    lineIndex = clearWhiteCharacters(line, length, FIRST_INDEX);

    if (lineIndex == length) { /* End of Line */
        return false;
    }

    lineIndex = readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    if (isComment(line, startOfWord)) { /* Skipping comment line */
        return false;
    }

    if ((hasLabel = isLabel(line, endOfWord))) { /* Marking label if any */
        startOfLabel = startOfWord;
        endOfLabel = endOfWord - 1;
        lineIndex = clearWhiteCharacters(line, length, endOfWord + 1);
        lineIndex = readNextWord(line, lineIndex, &startOfWord, &endOfWord);
    }

    if (isGuidanceLine(line, startOfWord)) {
        hasError = _analyzeGuidanceLine(pfp, line, length, lineIndex, startOfWord, endOfWord, &hasLabel);
    } else {
        hasError = _analyzeInstructionLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    }



    return hasError;
}

/* Analyze a guidance line */
static Boolean _analyzeGuidanceLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord, Boolean *hasLabel)
{
    Boolean hasError;

    hasError = false;

    if (0 == strncmp(line + startOfWord, GUIDANCE_DATA, strlen(GUIDANCE_DATA))) {
        /* Data line */
        hasError = _analyzeDataLine(pfp, line, length, lineIndex);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_STRUCT, strlen(GUIDANCE_STRUCT))) {
        /* Struct line */
        hasError = _analyzeStructLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_STRING, strlen(GUIDANCE_STRING))) {
        /* String line */
        hasError = _analyzeStringLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_ENTRY, strlen(GUIDANCE_ENTRY))) {
        /* Entry line */
        if (*hasLabel) {
            logError(labelWithEntry, NULL);
            *hasLabel = false;
        }
        hasError = _analyzeEntryLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    } else if (0 == strncmp(line + startOfWord, GUIDANCE_EXTERN, strlen(GUIDANCE_EXTERN))) {
        /* Extern line */
        if (*hasLabel) {
            logError(labelWithExtern, NULL);
            *hasLabel = false;
        }
        hasError = _analyzeExternLine(pfp, line, length, lineIndex, startOfWord, endOfWord);
    }
    return hasError;
}

/* Analyze an instruction line */
static Boolean _analyzeInstructionLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{
    Boolean hasError;

    hasError = false;

    return hasError;
}

static Boolean _analyzeDataLine(ParsedFile *pfp, const char *line, const int length, int lineIndex)
{
    int sign, c, data;
    Boolean hasError;

    hasError = false;
    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    while (lineIndex != length && hasError == false) {
        data = 0, sign = 1;
        if ((c = *(line + lineIndex)) == '-' || c == '+') {
            sign = c == '-' ? -1 : 1;
            lineIndex++;
        }
        while (lineIndex != length && isdigit(c = *(line + lineIndex))) {
            data = (data * 10) + (c - '0');
            lineIndex++;
        }
        if (lineIndex != length) {
            logError(undefinedData, NULL);
            pfp->hasError = true;
            break;
        }
        hasError = addData(pfp, (data * sign));
        lineIndex = clearWhiteCharOrComma(line, length, lineIndex);
    }
    return hasError;
}

static Boolean _analyzeStructLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}

static Boolean _analyzeStringLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}

static Boolean _analyzeEntryLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}

static Boolean _analyzeExternLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}
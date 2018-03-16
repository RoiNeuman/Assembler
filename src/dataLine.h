#ifndef ASSEMBLER_DATALINE_H
#define ASSEMBLER_DATALINE_H

#include "utils.h"
#include "assembler.h"

/* Analyze a data line of numbers */
Boolean analyzeDataLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

/* Analyze a struct line data of strings and numbers */
Boolean analyzeStructLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

/* Analyze a string line of characters */
Boolean analyzeStringLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

/* Analyze an entry line of inner label */
Boolean analyzeEntryLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

/* Analyze an extern line */
Boolean analyzeExternLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

#endif
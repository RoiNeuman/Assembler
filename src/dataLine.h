#ifndef ASSEMBLER_DATALINE_H
#define ASSEMBLER_DATALINE_H

#include "utils.h"
#include "assembler.h"

Boolean _analyzeDataLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

Boolean _analyzeStructLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

Boolean _analyzeStringLine(ParsedFile *pfp, const char *line, int length, int lineIndex);

Boolean _analyzeEntryLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);

Boolean _analyzeExternLine(ParsedFile *pfp, const char *line, int length, int lineIndex, int startOfWord, int endOfWord);

#endif

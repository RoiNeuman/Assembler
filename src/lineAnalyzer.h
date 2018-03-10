#ifndef ASSEMBLER_LINEANALYZER_H
#define ASSEMBLER_LINEANALYZER_H

#include "assembler.h"
#include "parser.h"
#include "utils.h"

/* Analyze the given line */
Boolean analyzeLine(ParsedFile *pfp, const char *line, int length);

#endif
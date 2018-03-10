#ifndef ASSEMBLER_LINEANALYZER_H
#define ASSEMBLER_LINEANALYZER_H

#include "parser.h"
#include "utils.h"

/* Types of assembly line */
typedef enum LineType {
    guidance,
    instruction
} LineType;

/* Analyze the given line */
Boolean analyzeLine(ParsedFile *pfp, const char *line, int length);

#endif
#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <stdio.h>
#include "assembler.h"

#define FIRST_INDEX 0
#define GUIDANCE_DATA ".data"
#define GUIDANCE_STRUCT ".struct"
#define GUIDANCE_STRING ".string"
#define GUIDANCE_ENTRY ".entry"
#define GUIDANCE_EXTERN ".extern"

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName);

/* Return the next index in the line which is not a white character */
int clearWhiteCharacters(const char *line, int length, int index);

/* Return the next index in the line which is not a white character or comma */
int clearWhiteCharOrComma(const char *line, const int length, int index);

/* Read the next word from a line */
/* Return the next index after the word */
int readNextWord(const char *line, int index, int *start, int *end);

#endif
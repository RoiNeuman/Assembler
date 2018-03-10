#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <stdio.h>

#define FIRST_INDEX 0

/* Parsed file type */
typedef struct ParsedFile {
    char *fName;

} ParsedFile;

typedef enum LineType {
    comment,

} LineType;

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName);

#endif
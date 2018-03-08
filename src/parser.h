#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <stdio.h>

/* Parsed file type */
typedef  struct ParsedFile {
    char *fName;

} ParsedFile;

/* Parse a given source file */
ParsedFile parseFile(FILE *fp, char *fName);

#endif
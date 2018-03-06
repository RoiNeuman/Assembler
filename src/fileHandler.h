#ifndef ASSEMBLER_FILEHANDLER_H
#define ASSEMBLER_FILEHANDLER_H

#include "utils.h"
#include "errors.h"

#define AS_EXTENSION ".as"
#define READ_MODE "r"

/* Adds extension to the file name */
char *addFileExtension(const char *pName, const char *pExtension);

/* Checks availability and open an assembly file for reading */
FILE *getAssemblyFile(char *fName);

#endif

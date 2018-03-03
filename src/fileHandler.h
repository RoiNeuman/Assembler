#ifndef ASSEMBLER_FILEHANDLER_H
#define ASSEMBLER_FILEHANDLER_H

#include "utils.h"
#include "errors.h"

#define AS_EXTENSION ".as"

/* Checks file availability */
Error checkFile(char *argv);

/* Adds extension to the file name */
char *addFileExtension(const char *pName, const char *pExtension);

/* Checks availability and open an assembly file for reading */
Error getAssemblyFile(char *fName, FILE *fp);

#endif

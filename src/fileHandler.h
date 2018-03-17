#ifndef ASSEMBLER_FILEHANDLER_H
#define ASSEMBLER_FILEHANDLER_H

#include <stdio.h>

#define AS_EXTENSION ".as"
#define READ_MODE "r"
#define WRITE_MODE "w"

/* Adds extension to the file name */
char *addFileExtension(const char *pName, const char *pExtension);

/* Checks availability and open an assembly file for reading */
FILE *getAssemblyFile(char *fName);

/* Closing the given file */
void closeFile(FILE *fp, char * fName);

/* Create file and fill it with given content */
void createFileWithContent(const char *fName, const char *content);

#endif

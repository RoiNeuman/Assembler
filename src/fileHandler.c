#include <stdio.h>
#include "fileHandler.h"
#include "utils.h"
#include "errors.h"

/* Adds extension to the file name */
char *addFileExtension(const char *pName, const char *pExtension)
{
    return stringConcat(pName, pExtension);
}

/* Checks availability and open an assembly file for reading */
FILE *getAssemblyFile(char *fName)
{
    FILE *fp;
    char *pFullName;

    pFullName = addFileExtension(fName, AS_EXTENSION);

    if (pFullName == NULL) {
        logError(outOfMemory, "Adding file extension, getAssemblyFile().");
    }

    fp = fopen(pFullName, READ_MODE);

    if (fp == NULL) {
        logError(fileNotAvailable, pFullName);
    }

    return fp;
}

/* Closing the given file */
void closeFile(FILE *fp, char * fName)
{
    if (fclose(fp) != 0) {
        logError(fileNotClose, fName);
    }
}
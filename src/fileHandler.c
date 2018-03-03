#include <stdio.h>
#include <unistd.h>
#include "fileHandler.h"

/* Checks file availability */
Error checkFile(char *pFileName)
{
    /* Check if the file exists */
    if (pFileName != NULL && access(pFileName, F_OK) != -1) {
        return none;
    }
    return fileNotExist;
}

/* Adds extension to the file name */
char *addFileExtension(const char *pName, const char *pExtension)
{
    return stringConcat(pName, pExtension);
}

/* Checks availability and open an assembly file for reading */
Error getAssemblyFile(char *fName, FILE *fp)
{
    char *pFullName;

    pFullName = addFileExtension(fName, AS_EXTENSION);

    if (pFullName == NULL) {
        return outOfMemory;
    }

    error = checkFile(argv[i]);
}

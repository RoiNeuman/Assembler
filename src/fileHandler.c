#include <stdio.h>
#include <unistd.h>
#include "fileHandler.h"

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
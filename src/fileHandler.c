#include <stdlib.h>
#include <unistd.h>
#include "fileHandler.h"
#include "utils.h"

Error checkFile(const char *pFileName)
{
    char *pFullName;

    /* Adds .as extension to the file name */
    pFullName = stringConcat(pFileName, AS_EXTENSION);
    if (pFullName == NULL) return outOfMemory;

    /* Check file name's extension (.as) , check file exist */
    if (access(pFullName, F_OK) != -1) {
        free(pFullName);
        return none;
    }
    free(pFullName);
    return fileNotExist;
}
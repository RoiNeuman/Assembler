#include <stdio.h>
#include "assembler.h"
#include "errors.h"
#include "fileHandler.h"
#include "memoryManager.h"

int main(int argc, char *argv[])
{
    int i;
    char *pFullName;
    Error error;

    for (i = 1; i < argc; ++i) {
        pFullName = addFileExtension(argv[i], AS_EXTENSION);
        if (pFullName == NULL) {
            error = outOfMemory;
        } else {
            error = checkFile(argv[i]);
        }
        if (error == none) {
            /* parseFile(argv[i]);
            createResultFile(); */
        } else {
            printError(error);
        }
        freeAll();
    }
    freeAll();

    return 0;
}
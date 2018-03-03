#include <stdio.h>
#include "assembler.h"
#include "fileHandler.h"
#include "memoryManager.h"

Error runAssemblerOnFile(char *fName)
{
    Error error;
    FILE *fp;
    ParsedFile pParsed;

    fp = NULL;
    error = getAssemblyFile(fName, fp);

    if (error != none) {
        return error;
    }

    error = parseFile(fp, pParsed);

    if (error != none) {
        return error;
    }

    error = createResultFile(pParsed);

    return error;
}

int main(int argc, char *argv[])
{
    int i;
    Error error;

    for (i = 1; i < argc; ++i) {
        /* Running the assembler of the file given by the argument */
        error = runAssemblerOnFile(argv[i]);
        if (error != none) {
            /* Printing Errors */
            printError(error);
        }
        freeAll();
    }

    return 0;
}
#include <stdio.h>
#include "assembler.h"
#include "fileHandler.h"
#include "memoryManager.h"
#include "parser.h"
#include "errors.h"

/* Run the assembler on a file */
void runAssemblerOnFile(char *fName)
{
    FILE *fp;
    ParsedFile *pParsed;

    fp = getAssemblyFile(fName);
    if (fp != NULL) {
        pParsed = parseFile(fp, fName);
        closeFile(fp, fName);
        /* createResultFile(pParsed); */
    }
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; ++i) {
        /* Running the assembler of the file given by the argument */
        runAssemblerOnFile(argv[i]);
        /* Error printing */
        printAllErrors();
        /* Freeing all allocated memory */
        freeAll();
    }

    return 0;
}
#include "assembler.h"
#include "memoryManager.h"
#include "errors.h"

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
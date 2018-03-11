#include <stdio.h>
#include "assembler.h"
#include "fileHandler.h"
#include "parser.h"
#include "memoryManager.h"
#include "errors.h"

/* Run the assembler on a file */
void runAssemblerOnFile(char *fName)
{
    FILE *fp;
    ParsedFile *pfp;

    fp = getAssemblyFile(fName);
    if (fp != NULL) {
        pfp = parseFile(fp, fName);
        closeFile(fp, fName);
        if (pfp != NULL) {
            /* createResultFile(pParsed); */
        }
    }
}

/* Initializing new ParsedFile struct */
ParsedFile *initializeParsedFile(char *fName)
{
    ParsedFile *pfp;

    /* Allocating memory for the ParsedFile struct */
    pfp = (ParsedFile *)autoDispMalloc(sizeof(ParsedFile));

    if (pfp == NULL) {
        logError(outOfMemory, "Allocating parseFile struct, initializeParsedFile()");
        return NULL;
    }

    pfp->fName = fName;
    pfp->IC = 0;
    pfp->DC = 0;
    pfp->hasError = false;

    return pfp;
}

/* Add data to the data list */
Boolean addData(ParsedFile *pfp, int data)
{

}
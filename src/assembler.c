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

    /* Initialize the new struct properties */
    pfp->fName = fName;
    pfp->IC = 0;
    pfp->DC = 0;
    pfp->hasError = false;
    pfp->iList = NULL;
    pfp->dList = NULL;
    pfp->lList = NULL;

    return pfp;
}

/* Add data to the data list */
Boolean addData(ParsedFile *pfp, int data)
{
    Data *newData, *prev;

    newData = (Data *)autoDispMalloc(sizeof(Data));

    if (newData == NULL) {
        logError(outOfMemory, "Adding new data to the data list.");
        return true;
    }

    /* Adding the new struct properties */
    newData->value = data;
    newData->next = NULL;

    /* Adding the new data struct to the data list */
    if (pfp->dList == NULL) {
        /* First data in the data list */
        pfp->dList = newData;
    } else {
        prev = pfp->dList;
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = newData;
    }
    pfp->DC++; /* Incrementing the data counter */
    return false;
}
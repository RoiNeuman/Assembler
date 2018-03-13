#include <stdio.h>
#include <string.h>
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

/* Add label to the labels list */
Boolean addLabel(ParsedFile *pfp, const char *line, const int start, const int end, CounterType ct, Boolean hasEntry, Boolean hasExtern)
{
    int i;
    Boolean existingLabel;
    Label *newLabel, *prev;

    prev = pfp->lList;
    /* Checking new label or existing label */
    if (pfp->lList != NULL) {
        while (prev->next != NULL) {
            existingLabel = true;
            for (i = 0; i < strlen(prev->name) && (i + start) <= end; ++i) {
                if (*(prev->name + i) != *(line + (i + start))) {
                    existingLabel = false;
                    break;
                }
            }
            if (existingLabel) {
                break;
            }
            prev = prev->next;
        }
        if (prev->next != NULL) {
            /* Existing label */
            prev->hasEntry = (hasEntry ? hasEntry : prev->hasEntry);
            prev->hasExtern = (hasExtern ? hasExtern : prev->hasExtern);
            if (start == LABEL_START_POSITION) {
                switch (ct) {
                    case IC:
                        prev->counter = pfp->IC;
                        prev->ct = IC;
                        break;
                    case DC:
                        prev->counter = pfp->DC;
                        prev->ct = DC;
                        break;
                }
            }
            return addLineCounter(pfp, prev, ct);
        }
    }
    /* New label */
    newLabel = (Label *)autoDispMalloc(sizeof(Label));

    if (newLabel == NULL) {
        logError(outOfMemory, "Adding new label to the label list.");
        return true;
    }

    /* Adding the new label properties */
    if (start == LABEL_START_POSITION) {
        switch (ct) {
            case IC:
                newLabel->counter = pfp->IC;
                newLabel->ct = IC;
                break;
            case DC:
                newLabel->counter = pfp->DC;
                newLabel->ct = DC;
                break;
        }
    } else {
        newLabel->counter = LABEL_WITHOUT_DECLERATION;
    }

    newLabel->hasEntry = (hasEntry ? hasEntry : newLabel->hasEntry);
    newLabel->hasExtern = (hasExtern ? hasExtern : newLabel->hasExtern);
    newLabel->next = NULL;

    /* Adding the new label to the list */
    if (prev != NULL) {
        prev->next = newLabel;
    } else {
        pfp->lList = newLabel;
    }
    return addLineCounter(pfp, newLabel, ct);
}

/* Add new line counter to a label */
Boolean addLineCounter(ParsedFile *pfp, Label *label, CounterType ct)
{
    LineCounter *lc;

    lc = label->lines;
    while (lc != NULL) {
        lc = lc->next;
    }

    /* Allocating new line counter */
    lc = (LineCounter *)autoDispMalloc(sizeof(LineCounter));

    if (lc == NULL) {
        logError(outOfMemory, "Adding new line to the label.");
        return true;
    }

    /* Adding the new line counter properties */
    switch (ct) {
        case IC:
            lc->counter = pfp->IC;
            lc->ct = IC;
            break;
        case DC:
            lc->counter = pfp->DC;
            lc->ct = DC;
            break;
    }
    return false;
}
#include <stdio.h>
#include <string.h>
#include "assembler.h"
#include "resultFilesHandler.h"
#include "fileHandler.h"
#include "parser.h"
#include "memoryManager.h"
#include "errors.h"

static int line;

/* Run the assembler on a file */
void runAssemblerOnFile(char *fName)
{
    FILE *fp;
    ParsedFile *pfp;

    line = 0;
    initErrorLogger();
    fp = getAssemblyFile(fName);
    if (fp != NULL) {
        pfp = parseFile(fp, fName);
        closeFile(fp, fName);
        if (pfp != NULL && pfp->hasError == false) {
            /* Legal parsed file */
            createResultFiles(pfp);
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
    newData->line = line;
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

    /* Incrementing the data counter */
    pfp->DC++;

    /* No errors */
    return false;
}

/* Add label to the labels list */
Boolean addLabel(ParsedFile *pfp, const char *line, const int start, const int end, CounterType ct, Boolean hasEntry, Boolean hasExtern)
{
    int i;
    Boolean existingLabel;
    Label *newLabel, *label;

    existingLabel = false;
    label = pfp->lList;
    /* Checking new label or existing label */
    if (label != NULL) {
        while (label != NULL) {
            existingLabel = true;
            for (i = 0; i < strlen(label->name) && (i + start) <= end; ++i) {
                if (*(label->name + i) != *(line + (i + start))) {
                    existingLabel = false;
                    break;
                }
            }
            if (existingLabel == false && label->next != NULL) {
                label = label->next;
            } else {
                break;
            }
        }
        if (existingLabel) {
            /* Existing label */
            label->hasEntry = (hasEntry ? hasEntry : label->hasEntry);
            label->hasExtern = (hasExtern ? hasExtern : label->hasExtern);
            if (start == LABEL_START_POSITION) {
                switch (ct) {
                    case IC:
                        label->counter = pfp->IC;
                        label->ct = IC;
                        break;
                    case DC:
                        label->counter = pfp->DC;
                        label->ct = DC;
                        break;
                }
            }
            return addLineCounter(pfp, label, ct);
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
        newLabel->counter = LABEL_WITHOUT_DECLARATION;
    }

    /* Adding the new struct properties */
    newLabel->name = substring(line, start, (end - start + 1));
    if (newLabel->name == NULL) {
        logError(outOfMemory, "Adding new label.");
        return true;
    }
    newLabel->hasEntry = (hasEntry ? hasEntry : newLabel->hasEntry);
    newLabel->hasExtern = (hasExtern ? hasExtern : newLabel->hasExtern);
    newLabel->next = NULL;

    /* Adding the new label to the list */
    if (label != NULL) {
        label->next = newLabel;
    } else {
        pfp->lList = newLabel;
    }

    /* Marking this line for this label */
    return addLineCounter(pfp, newLabel, ct);
}

/* Add new line counter to a label */
Boolean addLineCounter(ParsedFile *pfp, Label *label, CounterType ct)
{
    LineCounter *lc, *prev;

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
    lc->next = NULL;

    /* Adding the new line counter to the list */
    if (label->lines == NULL) {
        label->lines = lc;
    } else {
        prev = label->lines;
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = lc;
    }

    /* No errors */
    return false;
}

/* Add new no operands instruction to the instructions list */
Boolean addNoOperandsInstruction(ParsedFile *pfp, Opcode op)
{
    Instruction *newInstruction, *prev;

    /* Allocating memory for the new instruction */
    newInstruction = (Instruction *)autoDispMalloc(sizeof(Instruction));

    if (newInstruction == NULL) {
        logError(outOfMemory, "Adding no operands instruction.");
        return true;
    }

    /* Adding the new struct properties */
    newInstruction->oc = op;
    newInstruction->instructionType = noOperands;
    newInstruction->source = NULL;
    newInstruction->destination = NULL;
    newInstruction->line = line;
    newInstruction->next = NULL;

    /* Adding the new instruction to the instructions list */
    if (pfp->iList == NULL) {
        /* First instruction */
        pfp->iList = newInstruction;
    } else {
        prev = pfp->iList;
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = newInstruction;
    }

    /* Incrementing the instructions counter */
    pfp->IC = pfp->IC + IC_INSTRUCTION;

    /* No errors */
    return false;
}

/* Create new operand struct with initial values */
Boolean createOperand(Operand **ppOperand, OperandType operandType, int iData, char *strData)
{
    /* Allocating memory for a new operand */
    *ppOperand = (Operand *)autoDispMalloc(sizeof(Operand));

    if (*ppOperand == NULL) {
        logError(outOfMemory, NULL);
        return true;
    }

    (*ppOperand)->type = operandType;
    (*ppOperand)->iData = iData;
    (*ppOperand)->strData = strData;

    return false;
}

/* Add new instruction with only one operand to the instruction list */
Boolean addSingleOperandInstruction(ParsedFile *pfp, Opcode op, Operand *pDestination)
{
    Instruction *newInstruction, *prev;

    /* Allocating memory for the new instruction */
    newInstruction = (Instruction *)autoDispMalloc(sizeof(Instruction));

    if (newInstruction == NULL) {
        logError(outOfMemory, "Adding no operands instruction.");
        return true;
    }

    /* Adding the new struct properties */
    newInstruction->oc = op;
    newInstruction->instructionType = singleOperand;
    newInstruction->source = NULL;
    newInstruction->destination = pDestination;
    newInstruction->line = line;
    newInstruction->next = NULL;

    /* Adding the new instruction to the instructions list */
    if (pfp->iList == NULL) {
        /* First instruction */
        pfp->iList = newInstruction;
    } else {
        prev = pfp->iList;
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = newInstruction;
    }

    /* Incrementing the instructions counter */
    if (pDestination->type == structAddressing) {
        pfp->IC = pfp->IC + IC_INSTRUCTION + IC_OPERAND_STRUCT;
    } else {
        pfp->IC = pfp->IC + IC_OPERAND;
    }

    /* No errors */
    return false;
}

/* Add new instruction with two operands to the instruction list */
Boolean addTwoOperandInstruction(ParsedFile *pfp, Opcode op, Operand *pSource, Operand *pDestination)
{
    Instruction *newInstruction, *prev;

    /* Allocating memory for the new instruction */
    newInstruction = (Instruction *)autoDispMalloc(sizeof(Instruction));

    if (newInstruction == NULL) {
        logError(outOfMemory, "Adding no operands instruction.");
        return true;
    }

    /* Adding the new struct properties */
    newInstruction->oc = op;
    newInstruction->instructionType = twoOperands;
    newInstruction->source = pSource;
    newInstruction->destination = pDestination;
    newInstruction->line = line;
    newInstruction->next = NULL;

    /* Adding the new instruction to the instructions list */
    if (pfp->iList == NULL) {
        /* First instruction */
        pfp->iList = newInstruction;
    } else {
        prev = pfp->iList;
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = newInstruction;
    }

    /* Incrementing the instructions counter */
    if (pSource->type == structAddressing && pDestination->type == structAddressing) {
        pfp->IC = pfp->IC + IC_INSTRUCTION + IC_OPERAND_STRUCT + IC_OPERAND_STRUCT;
    } else if (pSource->type == structAddressing || pDestination->type == structAddressing) {
        pfp->IC = pfp->IC + IC_INSTRUCTION + IC_OPERAND + IC_OPERAND_STRUCT;
    } else if (pSource->type == registerAddressing || pDestination->type == registerAddressing) {
        pfp->IC = pfp->IC + IC_INSTRUCTION + IC_OPERAND;
    } else {
        pfp->IC = pfp->IC + IC_INSTRUCTION + IC_OPERAND + IC_OPERAND;
    }

    /* No errors */
    return false;
}

/* Set the source file line to a given number */
void setSourceFileLine(int number)
{
    line = number;
}
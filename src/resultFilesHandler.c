#include <string.h>
#include "resultFilesHandler.h"
#include "mozarUtils.h"
#include "memoryManager.h"
#include "fileHandler.h"
#include "errors.h"

char *createObjectFileEmptyString(ParsedFile *pfp, int *objectFileLength, char **mozarInstructionLength, char **mozarDataLength);
int writeInstruction(ParsedFile *pfp, char *strObjectFile, Instruction *instruction, int addressCounter);
int writeInstructionWord(char *strObjectFile, Instruction *instruction, int addressCounter);
int writeOperand(ParsedFile *pfp, char *strObjectFile, Instruction *instruction, Operand *operand, int
addressCounter, Boolean isSource);
int writeRegistersOperands(char *strObjectFile, Instruction *instruction, int addressCounter);
int searchLabel(ParsedFile *pfp, const char *name, int *labelType);
int writeData(char *strObjectFile, Data *data, int addressCounter);
void createEntryFile(ParsedFile *pfp);
void createExternFile(ParsedFile *pfp);

void createResultFiles(ParsedFile *pfp)
{
    int objectFileLength, addressCounter;
    char *strObjectFile, *mozarInstructionLength, *mozarDataLength, *objectFileName;
    Instruction *instruction;
    Data *data;

    mozarInstructionLength = NULL;
    mozarDataLength = NULL;
    instruction = pfp->iList;
    data = pfp->dList;
    addressCounter = INITIAL_ADDRESS;
    strObjectFile = createObjectFileEmptyString(pfp, &objectFileLength, &mozarInstructionLength, &mozarDataLength);

    if (strObjectFile == NULL || mozarInstructionLength == NULL || mozarDataLength == NULL) {
        return;
    }

    /* Writing first line */
    strcat(strObjectFile, mozarInstructionLength);
    strcat(strObjectFile, SPACE_STRING);
    strcat(strObjectFile, mozarDataLength);
    strcat(strObjectFile, END_LINE_STRING);

    /* Running over the instruction list */
    while (instruction != NULL) {
        addressCounter = writeInstruction(pfp, strObjectFile, instruction, addressCounter);
        if (addressCounter == INSTRUCTION_ERROR) {
            return;
        }
        instruction = instruction->next;
    }

    /* Running over the data list */
    while (data != NULL) {
        addressCounter = writeData(strObjectFile, data, addressCounter);
        data = data->next;
    }

    objectFileName = stringConcat(pfp->fName, OBJECT_FILE_EXTENTION);

    if (objectFileName == NULL) {
        logError(outOfMemory, "Creating object file.");
        return;
    }
    createFileWithContent(objectFileName, strObjectFile);
    createEntryFile(pfp);
    createExternFile(pfp);

    /* Writing terminating character */
    *(strObjectFile + strlen(strObjectFile)) = '\0';
}

/* Initialize string in the length of the result object file */
char *createObjectFileEmptyString(ParsedFile *pfp, int *objectFileLength, char **mozarInstructionLength, char **mozarDataLength)
{
    int iInstructionLength, iDataLength, lineLength, _ic, _dc;
    char *strObjectFile;

    _ic = (pfp->IC != 0 ? pfp->IC - IC_OPERAND : 0);
    _dc = (pfp->DC != 0 ? pfp->DC - IC_OPERAND : 0);

    *mozarInstructionLength = binaryToMozar(decimalToBinary(_ic), false);
    *mozarDataLength = binaryToMozar(decimalToBinary(_dc), false);
    iInstructionLength = strlen(*mozarInstructionLength);
    iDataLength = strlen(*mozarDataLength);
    lineLength = (ADDRESS_IN_MOZAR_LENGTH + WORD_IN_MOZAR_LENGTH + SPACE_AND_END_LINE_LENGTH);

    /* Calculating the object file length in characters */
    *objectFileLength = iInstructionLength + iDataLength + SPACE_AND_END_LINE_LENGTH + (lineLength * pfp->IC) + (lineLength * pfp->DC) + TERMINATE_STRING_LENGTH;

    /* Allocating memory for the object file */
    strObjectFile = (char *)autoDispMalloc(sizeof(char) * (*objectFileLength));

    if (strObjectFile == NULL) {
        logError(outOfMemory, "Allocating memory for the object file.");
        return NULL;
    }

    /* Initialize empty string */
    *strObjectFile = '\0';

    return strObjectFile;
}

/* Write an instruction to the object file's result string */
int writeInstruction(ParsedFile *pfp, char *strObjectFile, Instruction *instruction, int addressCounter)
{
    /* Write the instruction itself */
    addressCounter = writeInstructionWord(strObjectFile, instruction, addressCounter);

    /* For 2 registers operands there is only 1 word */
    if (instruction->instructionType == twoOperands && instruction->source->type == registerAddressing && instruction->destination->type == registerAddressing) {
        /* Write 2 registers operands */
        addressCounter = writeRegistersOperands(strObjectFile, instruction, addressCounter);
    } else {
        if (instruction->instructionType == twoOperands) {
            /* Write the source operand */
            addressCounter = writeOperand(pfp, strObjectFile, instruction, instruction->source, addressCounter, true);
        }

        if (instruction->instructionType == twoOperands || instruction->instructionType == singleOperand) {
            /* Write the destination operand */
            addressCounter = writeOperand(pfp, strObjectFile, instruction, instruction->destination, addressCounter, false);
        }
    }

    return addressCounter;
}

/* Write the instruction word itself to the object file's result string */
int writeInstructionWord(char *strObjectFile, Instruction *instruction, int addressCounter)
{
    int iWord;

    iWord = instruction->oc * INSTRUCTION_NAME_POSITION_MULTIPLIER;

    /* Operands' types */
    if (instruction->instructionType == singleOperand) {
        iWord += instruction->destination->type * DESTINATION_OPERAND_POSITION_MULTIPLIER;
    } else if (instruction->instructionType == twoOperands) {
        iWord += instruction->source->type * SOURCE_OPERAND_POSITION_MULTIPLIER;
        iWord += instruction->destination->type * DESTINATION_OPERAND_POSITION_MULTIPLIER;
    }

    /* Writing instruction line */
    strcat(strObjectFile, binaryToMozar(decimalToBinary(addressCounter), true));
    strcat(strObjectFile, SPACE_STRING);
    strcat(strObjectFile, binaryToMozar(decimalToBinary(iWord), true));
    strcat(strObjectFile, END_LINE_STRING);

    addressCounter++;
    return addressCounter;
}

/* Write an operand of the instruction to the object file's result string */
int writeOperand(ParsedFile *pfp, char *strObjectFile, Instruction *instruction, Operand *operand, int
addressCounter, Boolean isSource)
{
    int iWord, labelAddress, labelType;

    iWord = 0;
    switch (operand->type) {
        case immediateAddressing:
            iWord = operand->iData * OPERAND_MULTIPLIER;
            break;
        case directAddressing:
            labelAddress = searchLabel(pfp, operand->strData, &labelType);
            if (labelAddress == INSTRUCTION_ERROR) {
                setErrorLoggerLine(instruction->line);
                logError(labelNotFound, NULL);
                return INSTRUCTION_ERROR;
            }
            iWord = (labelAddress * OPERAND_MULTIPLIER) + labelType;
            break;
        case structAddressing:
            labelAddress = searchLabel(pfp, operand->strData, &labelType);
            if (labelAddress == INSTRUCTION_ERROR) {
                setErrorLoggerLine(instruction->line);
                logError(structNotFound, NULL);
                return INSTRUCTION_ERROR;
            } else {
                /* Writing struct name location line */
                strcat(strObjectFile, binaryToMozar(decimalToBinary(addressCounter), true));
                strcat(strObjectFile, SPACE_STRING);
                strcat(strObjectFile, binaryToMozar((decimalToBinary(labelAddress)<<OPERAND_OFFSET) + labelType, true));
                strcat(strObjectFile, END_LINE_STRING);
                addressCounter++;
            }
            iWord = operand->iData * OPERAND_MULTIPLIER;
            break;
        case registerAddressing:
            if (isSource) {
                iWord = operand->iData * DOUBLE_REGISTERS_MULTIPLIER;
            } else {
                iWord = operand->iData * OPERAND_MULTIPLIER;
            }
            break;
    }

    /* Writing instruction line */
    strcat(strObjectFile, binaryToMozar(decimalToBinary(addressCounter), true));
    strcat(strObjectFile, SPACE_STRING);
    strcat(strObjectFile, binaryToMozar(decimalToBinary(iWord), true));
    strcat(strObjectFile, END_LINE_STRING);

    addressCounter++;
    return addressCounter;
}

/* Write 2 registers operands */
int writeRegistersOperands(char *strObjectFile, Instruction *instruction, int addressCounter)
{
    int iWord;

    iWord = instruction->source->iData * DOUBLE_REGISTERS_MULTIPLIER;
    iWord += instruction->destination->iData * OPERAND_MULTIPLIER;

    /* Writing instruction line */
    strcat(strObjectFile, binaryToMozar(decimalToBinary(addressCounter), true));
    strcat(strObjectFile, SPACE_STRING);
    strcat(strObjectFile, binaryToMozar(decimalToBinary(iWord), true));
    strcat(strObjectFile, END_LINE_STRING);

    addressCounter++;
    return addressCounter;
}

/* Searching a given label in the labels' list */
int searchLabel(ParsedFile *pfp, const char *name, int *labelType)
{
    Label *label;

    label = pfp->lList;
    /* Searching for the label */
    while (label != NULL && strcmp(label->name, name) != 0) {
        label = label->next;
    }

    if (label == NULL) {
        /* Label not found */
        return INSTRUCTION_ERROR;
    }

    if (label->hasEntry) {
        *labelType = EXTERNAL;
        return 0;
    }

    *labelType = RELOCATABLE;
    if (label->ct == IC) {
        return (INITIAL_ADDRESS + label->counter);
    } else {
        return (INITIAL_ADDRESS + pfp->IC + label->counter);
    }
}

/* Write an data to the object file's result string */
int writeData(char *strObjectFile, Data *data, int addressCounter)
{
    /* Writing data line */
    strcat(strObjectFile, binaryToMozar(decimalToBinary(addressCounter), true));
    strcat(strObjectFile, SPACE_STRING);
    strcat(strObjectFile, binaryToMozar(decimalToBinary(data->value), true));
    strcat(strObjectFile, END_LINE_STRING);

    addressCounter++;
    return addressCounter;
}

void createEntryFile(ParsedFile *pfp)
{
    int address, contentLength;
    char *entryFileName, *strContentFile;
    Label *label;

    contentLength = 0;
    label = pfp->lList;

    while (label != NULL) {
        if (label->hasEntry && label->counter != LABEL_WITHOUT_DECLARATION) {
            contentLength += (strlen(label->name) + ADDRESS_IN_MOZAR_LENGTH + SPACE_AND_END_LINE_LENGTH);
        }
        label = label->next;
    }
    contentLength += TERMINATE_STRING_LENGTH;

    strContentFile = (char *)autoDispMalloc(sizeof(char) * contentLength);
    label = pfp->lList;

    while (label != NULL) {
        if (label->hasEntry && label->counter != LABEL_WITHOUT_DECLARATION) {
            strcat(strContentFile, label->name);
            strcat(strContentFile, SPACE_STRING);
            if (label->ct == IC) {
                address = INITIAL_ADDRESS + label->counter;
            } else {
                address = INITIAL_ADDRESS + pfp->IC + label->counter;
            }
            strcat(strContentFile, binaryToMozar(decimalToBinary(address), true));
            strcat(strContentFile, END_LINE_STRING);
        }
        label = label->next;
    }

    entryFileName = stringConcat(pfp->fName, ENTRY_FILE_EXTENTION);

    if (entryFileName == NULL) {
        setErrorLoggerLine(0);
        logError(outOfMemory, "Creating Entry file.");
        return;
    }
    createFileWithContent(entryFileName, strContentFile);
}

void createExternFile(ParsedFile *pfp)
{
    int address, contentLength;
    char *externFileName, *strContentFile;
    Label *label;
    LineCounter *lc;

    contentLength = 0;
    label = pfp->lList;

    while (label != NULL) {
        if (label->hasExtern) {
            lc = label->lines;
            while (lc != NULL) {
                contentLength += (strlen(label->name) + ADDRESS_IN_MOZAR_LENGTH + SPACE_AND_END_LINE_LENGTH);
                lc = lc->next;
            }
        }
        label = label->next;
    }
    contentLength += TERMINATE_STRING_LENGTH;

    strContentFile = (char *)autoDispMalloc(sizeof(char) * contentLength);
    label = pfp->lList;

    while (label != NULL) {
        if (label->hasExtern) {
            lc = label->lines;
            while (lc != NULL) {
                strcat(strContentFile, label->name);
                strcat(strContentFile, SPACE_STRING);
                if (lc->ct == IC) {
                    address = INITIAL_ADDRESS + lc->counter;
                } else {
                    address = INITIAL_ADDRESS + pfp->IC - IC_OPERAND + lc->counter;
                }
                strcat(strContentFile, binaryToMozar(decimalToBinary(address), true));
                strcat(strContentFile, END_LINE_STRING);
                lc = lc->next;
            }
        }
        label = label->next;
    }

    externFileName = stringConcat(pfp->fName, EXTERN_FILE_EXTENTION);

    if (externFileName == NULL) {
        setErrorLoggerLine(0);
        logError(outOfMemory, "Creating Extern file.");
        return;
    }
    createFileWithContent(externFileName, strContentFile);
}
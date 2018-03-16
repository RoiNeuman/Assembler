#include <stdio.h>
#include "errors.h"
#include "memoryManager.h"

static ErrorNode *head; /* The error list head pointer */

/* Filter and print single error */
void printError(Error e, const char *msg)
{
    switch (e) {
        case outOfMemory:
            fprintf(stderr, "Error: out of memory.\n");
            break;
        case fileNotAvailable:
            fprintf(stderr, "Error: file not available.\n");
            break;
        case fileNotClose:
            fprintf(stderr, "Error: fail to close file.\n");
            break;
        case readFromFileError:
            fprintf(stderr, "Error: reading from a file was failed.\n");
            break;
        case labelWithEntry:
            fprintf(stderr, "Warning: Label before .entry line.\n");
            break;
        case labelWithExtern:
            fprintf(stderr, "Warning: Label before .extern line.\n");
            break;
        case undefinedData:
            fprintf(stderr, "Error: Undefined character in .data line.\n");
            break;
        case labelStartPosition:
            fprintf(stderr, "Error: Label not the at the start of the line.\n");
            break;
        case labelFirstChar:
            fprintf(stderr, "Error: Label not start with a letter.\n");
            break;
        case labelMaxLength:
            fprintf(stderr, "Error: Label extends 30 characters.\n");
            break;
        case missedQuotationMark:
            fprintf(stderr, "Error: Missing quotation mark in string input.\n");
            break;
        case emptyEntryLine:
            fprintf(stderr, "Error: Empty entry line.\n");
            break;
        case emptyExternLine:
            fprintf(stderr, "Error: Empty extern line.\n");
            break;
        case missSourceOperand:
            fprintf(stderr, "Error: Missing a source operand in instruction line.\n");
            break;
        case missDestinationOperand:
            fprintf(stderr, "Error: Missing a destination operand in instruction line.\n");
            break;
        case undefinedInstruction:
            fprintf(stderr, "Error: Undefined instruction.\n");
            break;
        case undefinedSourceOperand:
            fprintf(stderr, "Error: Undefined source operand in an instruction line.\n");
            break;
        case undefinedDestinationOperand:
            fprintf(stderr, "Error: Undefined destination operand in an instruction line.\n");
            break;
        case none:
        default:
            break;
    }
    /* Printing extra message if any */
    if (msg != NULL) {
        fprintf(stderr, "->\t%s\n", msg);
    }
}

/* Printing all errors */
void printAllErrors()
{
    ErrorNode *pn;
    pn = head;

    /* Running over the error list and printing all the logged errors */
    while (pn != NULL) {
        printError(pn->error, pn->msg);
        pn = pn->next;
    }

    /* Clearing the error list (the memory will be free by the memoryManager) */
    head = NULL;
}

/* Log a new error into the error list */
void logError(Error e, const char *msg)
{
    ErrorNode *newError;
    ErrorNode *pn;
    ErrorNode *prev;

    /* Allocating memory for the new error */
    newError = (ErrorNode *)autoDispMalloc(sizeof(ErrorNode));

    if (newError == NULL) {
        /* Critical out of memory error, unable to log any more errors */
        printAllErrors();
        printError(e, msg);
        printError(outOfMemory, "Error handler, logError().");
        freeAll();
        exit(1);
    }

    newError->error = e;
    newError->msg = msg;
    newError->next = NULL;

    if (head == NULL) {
        /* First error in the error list */
        head = newError;
    } else {
        /* Adding the new error to the end of the error list */
        prev = head;
        pn = head->next;
        while (pn != NULL) {
            prev = pn;
            pn = pn->next;
        }
        prev->next = newError;
    }
}
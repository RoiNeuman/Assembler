#include <stdio.h>
#include "errors.h"
#include "memoryManager.h"

static ErrorNode *head; /* The error list head pointer */

/* Filter and print single error */
void printError(Error e, const char *msg)
{
    switch (e) {
        case outOfMemory:
            if (msg != NULL) {
                fprintf(stderr, "Error: out of memory. %s\n", msg);
            } else {
                fprintf(stderr, "Error: out of memory.\n");
            }
            break;
        case fileNotAvailable:
            if (msg != NULL) {
                fprintf(stderr, "Error: file not available. %s\n", msg);
            } else {
                fprintf(stderr, "Error: file not available.\n");
            }
            break;
        case fileNotClose:
            if (msg != NULL) {
                fprintf(stderr, "Error: fail to close file. %s\n", msg);
            } else {
                fprintf(stderr, "Error: fail to close file.\n");
            }
            break;
        case readFromFileError:
            if (msg != NULL) {
                fprintf(stderr, "Error: reading from a file was failed. %s\n", msg);
            } else {
                fprintf(stderr, "Error: reading from a file was failed.\n");
            }
            break;
        case labelWithEntry:
            if (msg != NULL) {
                fprintf(stderr, "Warning: Label before .entry line. %s\n", msg);
            } else {
                fprintf(stderr, "Warning: Label before .entry line.\n");
            }
            break;
        case labelWithExtern:
            if (msg != NULL) {
                fprintf(stderr, "Warning: Label before .extern line. %s\n", msg);
            } else {
                fprintf(stderr, "Warning: Label before .extern line.\n");
            }
            break;
        case none:
        default:
            break;
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
#include <stdio.h>
#include "errors.h"
#include "memoryManager.h"

static ErrorNode *head; /* The error list head pointer */
static int line;

/* Filter and print single error */
void printError(Error e, const char *msg, int _line)
{
    switch (e) {
        case outOfMemory:
            fprintf(stderr, "Line %d, Error: out of memory.\n", _line);
            break;
        case fileNotAvailable:
            fprintf(stderr, "Line %d, Error: file not available.\n", _line);
            break;
        case fileNotClose:
            fprintf(stderr, "Line %d, Error: fail to close file.\n", _line);
            break;
        case readFromFileError:
            fprintf(stderr, "Line %d, Error: reading from a file was failed.\n", _line);
            break;
        case labelWithEntry:
            fprintf(stderr, "Line %d, Warning: Label before .entry line.\n", _line);
            break;
        case labelWithExtern:
            fprintf(stderr, "Line %d, Warning: Label before .extern line.\n", _line);
            break;
        case undefinedData:
            fprintf(stderr, "Line %d, Error: Undefined character in .data line.\n", _line);
            break;
        case labelStartPosition:
            fprintf(stderr, "Line %d, Error: Label not the at the start of the line.\n", _line);
            break;
        case labelFirstChar:
            fprintf(stderr, "Line %d, Error: Label not start with a letter.\n", _line);
            break;
        case labelMaxLength:
            fprintf(stderr, "Line %d, Error: Label extends 30 characters.\n", _line);
            break;
        case missedQuotationMark:
            fprintf(stderr, "Line %d, Error: Missing quotation mark in string input.\n", _line);
            break;
        case emptyEntryLine:
            fprintf(stderr, "Line %d, Error: Empty entry line.\n", _line);
            break;
        case emptyExternLine:
            fprintf(stderr, "Line %d, Error: Empty extern line.\n", _line);
            break;
        case missSourceOperand:
            fprintf(stderr, "Line %d, Error: Missing a source operand in instruction line.\n", _line);
            break;
        case missDestinationOperand:
            fprintf(stderr, "Line %d, Error: Missing a destination operand in instruction line.\n", _line);
            break;
        case undefinedInstruction:
            fprintf(stderr, "Line %d, Error: Undefined instruction.\n", _line);
            break;
        case undefinedSourceOperand:
            fprintf(stderr, "Line %d, Error: Undefined source operand in an instruction line.\n", _line);
            break;
        case undefinedDestinationOperand:
            fprintf(stderr, "Line %d, Error: Undefined destination operand in an instruction line.\n", _line);
            break;
        case illegalImmediateAddressingOperand:
            fprintf(stderr, "Line %d, Error: Illegal immediate addressing operand in an instruction line.\n", _line);
            break;
        case structOperandWithoutName:
            fprintf(stderr, "Line %d, Error: Struct operand without a name.\n", _line);
            break;
        case structOperandWithoutProperty:
            fprintf(stderr, "Line %d, Error: Struct operand without a property.\n", _line);
            break;
        case structOperandPropertyNotNumber:
            fprintf(stderr, "Line %d, Error: Struct operand's property is not a number.\n", _line);
            break;
        case illegalRegisterOperand:
            fprintf(stderr, "Line %d, Error: Illegal register operand.\n", _line);
            break;
        case labelNotFound:
            fprintf(stderr, "Line %d, Error: Label not found.\n", _line);
            break;
        case structNotFound:
            fprintf(stderr, "Line %d, Error: Struct not found.\n", _line);
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
        printError(pn->error, pn->msg, pn->line);
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
        printError(e, msg, line);
        printError(outOfMemory, "Error handler, logError().", line);
        freeAll();
        exit(1);
    }

    newError->error = e;
    newError->line = line;
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

/* Initialze the error logger */
void initErrorLogger()
{
    head = NULL;
    line = -1;
}

/* Advance the logged line in the error logger */
void incrementErrorLoggerLine()
{
    line++;
}

/* Set the logged line to a given number */
void setErrorLoggerLine(int number)
{
    line = number;
}
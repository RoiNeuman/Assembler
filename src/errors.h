#ifndef ASSEMBLER_ERRORS_H
#define ASSEMBLER_ERRORS_H

/* All error types */
typedef enum Error {
    none,
    outOfMemory,
    fileNotAvailable,
    fileNotClose,
    readFromFileError,
    labelWithEntry,
    labelWithExtern,
    undefinedData,
    labelStartPosition,
    labelFirstChar,
    labelMaxLength,
    missedQuotationMark,
    emptyEntryLine,
    emptyExternLine,
    missSourceOperand,
    missDestinationOperand,
    undefinedInstruction,
    undefinedSourceOperand,
    undefinedDestinationOperand,
    illegalImmediateAddressingOperand,
    structOperandWithoutName,
    structOperandWithoutProperty,
    structOperandPropertyNotNumber,
    illegalRegisterOperand
} Error;

/* A node in the error list */
typedef struct ErrorNode {
    Error error; /* The relevant error */
    int line; /* The line number of this error */
    const char *msg; /* possible message */
    struct ErrorNode *next; /* The next error in the list */
} ErrorNode;

/* Filter and print single error */
void printError(Error e, const char *msg);

/* Printing all errors */
void printAllErrors();

/* Log a new error into the error list */
void logError(Error e, const char *msg);

/* Initialze the error logger */
void initErrorLogger();

/* Advance the logged line in the error logger */
void incrementErrorLoggerLine();

#endif
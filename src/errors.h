#ifndef ASSEMBLER_ERRORS_H
#define ASSEMBLER_ERRORS_H

typedef enum Error {
    none,
    outOfMemory,
    fileNotExist
} Error;

void printError(Error e);

#endif
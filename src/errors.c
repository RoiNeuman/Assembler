#include <stdio.h>
#include "errors.h"

void printError(Error e)
{
    /* Filter and print the error */
    switch (e) {
        case outOfMemory:
            fprintf(stderr, "Error: out of memory.\n");
            break;
        case fileNotExist:
            fprintf(stderr, "Error: file not exist.\n");
            break;
        case none:
        default:
            break;
    }
}

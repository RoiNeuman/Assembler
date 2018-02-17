#ifndef ASSEMBLER_MEMORYMANAGER_H
#define ASSEMBLER_MEMORYMANAGER_H

#include <stdlib.h>

/* Automatic disposed malloc */
void *autoDispMalloc(size_t bytes);

/* Frees all allocated memory in the buffer */
void freeAll();

#endif

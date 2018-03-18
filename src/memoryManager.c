#include "memoryManager.h"
#include <string.h>

#define BUFFER_INCREMENTS_SIZE 100

static void **buffer = NULL;
static long bufferSize = 0;
static long bufferPosition = 0;

/* Automatic disposed malloc */
void *autoDispMalloc(const size_t bytes)
{
    void *p = NULL;
    void **newBuffer = NULL;

    if (bufferSize <= bufferPosition) {
        newBuffer = malloc(sizeof(void *) * (bufferSize + BUFFER_INCREMENTS_SIZE));
        if (newBuffer == NULL) return NULL;

        buffer = memcpy(newBuffer, buffer, (sizeof(void *) * bufferSize));
        bufferSize += BUFFER_INCREMENTS_SIZE;
    }

    p = calloc(bytes, 1);
    if (p == NULL) return NULL;

    buffer[bufferPosition++] = p;
    return p;
}

/* Frees all allocated memory in the buffer */
void freeAll()
{
    while (0 < bufferPosition) {
        bufferPosition--;
        free(buffer[bufferPosition]);
        buffer[bufferPosition] = NULL;
    }
    free(buffer);
    buffer = NULL;
    bufferSize = 0;
}
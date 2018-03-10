#include "parser.h"
#include "memoryManager.h"
#include "errors.h"

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName)
{
    ParsedFile *pfp;

    pfp = (ParsedFile *)autoDispMalloc(sizeof(ParsedFile));

    if (pfp == NULL) {
        logError(outOfMemory, "Allocating parseFile struct, parseFile()");
        return NULL;
    }

    pfp->fName = fName;


    return pfp;
}
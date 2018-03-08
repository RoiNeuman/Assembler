#include "parser.h"
#include "memoryManager.h"

/* Parse a given source file */
ParsedFile parseFile(FILE *fp, char *fName)
{
    ParsedFile *pfp;

    pfp = (ParsedFile *)autoDispMalloc(sizeof(ParsedFile));

}
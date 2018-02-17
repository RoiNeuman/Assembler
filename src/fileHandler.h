#ifndef ASSEMBLER_FILEHANDLER_H
#define ASSEMBLER_FILEHANDLER_H

#include "utils.h"
#include "errors.h"

Error checkFile(char *argv);

char *addFileExtension(const char *pName, const char *pExtension);

#endif

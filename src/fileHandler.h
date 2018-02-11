#ifndef ASSEMBLER_FILEHANDLER_H
#define ASSEMBLER_FILEHANDLER_H

#include "utils.h"
#include "errors.h"

Error checkFile(String argv);

String addFileExtension(String pName, String pExtension);

#endif

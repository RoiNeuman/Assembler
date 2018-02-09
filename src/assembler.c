#include "assembler.h"
#include "errors.h"
#include "fileHandler.h"

int main(int argc, char *argv[])
{
    int i;
    Error error;

    for (i = 1; i < argc; ++i) {
        error = checkFile(argv[i]);
        if (error == none) {
            parseFile(argv[i]);
            createResultFile();
        } else {
            printError(error);
        }
    }

    return 0;
}
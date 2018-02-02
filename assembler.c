#include <stdio.h>
#include "assembler.h"

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; ++i) {
        checkFile(argv[i]);
        parseFile(argv[i]);
        createResultFile();
    }


    return 0;
}
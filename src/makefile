# -*- MakeFile -*-

all: assembler

assembler: assembler.o utils.o
	gcc -ansi -Wall -pedantic -o assembler assembler.o fileHandler.o utils.o errors.o

assembler.o: assembler.c assembler.h fileHandler.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c assembler.c assembler.h fileHandler.h utils.h errors.h

fileHandler.o: fileHandler.c fileHandler.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c fileHandler.c fileHandler.h utils.h errors.h

utils.o: utils.c utils.h
	gcc -ansi -Wall -pedantic -c utils.c utils.h

errors.o: errors.c errors.h
	gcc -ansi -Wall -pedantic -c errors.c errors.h

clean:
	rm *.o *.gch *~ assembler
# -*- MakeFile -*-

all: assembler

assembler: assembler.o utils.o
	gcc -ansi -Wall -pedantic -o assembler assembler.o utils.o

assembler.o: assembler.c assembler.h
	gcc -ansi -Wall -pedantic -c assembler.c assembler.h

utils.o: utils.c utils.h
	gcc -ansi -Wall -pedantic -c utils.c utils.h

clean:
	rm *.o *.gch *~ assembler
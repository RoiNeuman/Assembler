# -*- MakeFile -*-

all: assembler

assembler: main.o assembler.o lineAnalyzer.o parser.o fileHandler.o utils.o errors.o memoryManager.o
	gcc -ansi -Wall -pedantic -o assembler main.o assembler.o lineAnalyzer.o parser.o fileHandler.o utils.o errors.o memoryManager.o

main.o: main.c assembler.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c main.c assembler.h memoryManager.h errors.h

assembler.o: assembler.c assembler.h fileHandler.h parser.h
	gcc -ansi -Wall -pedantic -c assembler.c assembler.h fileHandler.h parser.h

lineAnalyzer.o: lineAnalyzer.c lineAnalyzer.h parser.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c lineAnalyzer.c lineAnalyzer.h parser.h utils.h errors.h

parser.o: parser.c parser.h memoryManager.h errors.h utils.h lineAnalyzer.h
	gcc -ansi -Wall -pedantic -c parser.c parser.h memoryManager.h errors.h utils.h lineAnalyzer.h

fileHandler.o: fileHandler.c fileHandler.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c fileHandler.c fileHandler.h utils.h errors.h

utils.o: utils.c utils.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c utils.c utils.h memoryManager.h errors.h

errors.o: errors.c errors.h memoryManager.h
	gcc -ansi -Wall -pedantic -c errors.c errors.h memoryManager.h

memoryManager.o: memoryManager.c memoryManager.h
	gcc -ansi -Wall -pedantic -c memoryManager.c memoryManager.h

clean:
	rm *.o *.gch *~ assembler
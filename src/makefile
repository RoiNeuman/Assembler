# -*- MakeFile -*-

all: assembler

assembler: main.o assembler.o resultFilesHandler.o lineAnalyzer.o dataLine.o instructionLine.o parser.o fileHandler.o utils.o mozarUtils.o errors.o memoryManager.o
	gcc -ansi -Wall -pedantic -o assembler main.o assembler.o resultFilesHandler.o lineAnalyzer.o dataLine.o instructionLine.o parser.o fileHandler.o utils.o mozarUtils.o errors.o memoryManager.o

main.o: main.c assembler.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c main.c assembler.h memoryManager.h errors.h

assembler.o: assembler.c assembler.h fileHandler.h resultFilesHandler.h parser.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c assembler.c assembler.h fileHandler.h resultFilesHandler.h parser.h memoryManager.h errors.h

resultFilesHandler.o: resultFilesHandler.c resultFilesHandler.h assembler.h mozarUtils.h memoryManager.h fileHandler.h errors.h
	gcc -ansi -Wall -pedantic -c resultFilesHandler.c resultFilesHandler.h assembler.h mozarUtils.h memoryManager.h fileHandler.h errors.h

parser.o: parser.c parser.h assembler.h memoryManager.h lineAnalyzer.h errors.h
	gcc -ansi -Wall -pedantic -c parser.c parser.h assembler.h memoryManager.h lineAnalyzer.h errors.h

lineAnalyzer.o: lineAnalyzer.c lineAnalyzer.h dataLine.h instructionLine.h parser.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c lineAnalyzer.c lineAnalyzer.h dataLine.h instructionLine.h parser.h utils.h errors.h

dataLine.o: dataLine.c dataLine.h assembler.h utils.h parser.h errors.h
	gcc -ansi -Wall -pedantic -c dataLine.c dataLine.h assembler.h utils.h parser.h errors.h

instructionLine.o: instructionLine.c instructionLine.h assembler.h utils.h memoryManager.h parser.h errors.h
	gcc -ansi -Wall -pedantic -c instructionLine.c instructionLine.h assembler.h utils.h memoryManager.h parser.h errors.h

fileHandler.o: fileHandler.c fileHandler.h utils.h errors.h
	gcc -ansi -Wall -pedantic -c fileHandler.c fileHandler.h utils.h errors.h

utils.o: utils.c utils.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c utils.c utils.h memoryManager.h errors.h

mozarUtils.o: mozarUtils.c mozarUtils.h utils.h memoryManager.h errors.h
	gcc -ansi -Wall -pedantic -c mozarUtils.c mozarUtils.h utils.h memoryManager.h errors.h

errors.o: errors.c errors.h memoryManager.h
	gcc -ansi -Wall -pedantic -c errors.c errors.h memoryManager.h

memoryManager.o: memoryManager.c memoryManager.h
	gcc -ansi -Wall -pedantic -c memoryManager.c memoryManager.h

clean:
	rm *.o *.gch *~ assembler

cleanO:
	rm *.o *.gch *~
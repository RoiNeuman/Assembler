cmake_minimum_required(VERSION 3.9)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(Assembler src/assembler.c src/assembler.h src/utils.c src/utils.h src/fileHandler.c src/fileHandler.h src/errors.c src/errors.h src/memoryManager.c src/memoryManager.h src/parser.c src/parser.h)
cmake_minimum_required(VERSION 3.9)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(Assembler assembler.c assembler.h utils.c utils.h)
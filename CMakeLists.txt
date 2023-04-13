cmake_minimum_required(VERSION 3.22)
project(Chip8 C)

set(CMAKE_C_STANDARD 23)

add_executable(Chip8 main.c loader.c main.h fetcher.c decoder.cpp)

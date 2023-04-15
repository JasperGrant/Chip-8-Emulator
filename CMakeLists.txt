cmake_minimum_required(VERSION 3.22)
project(Chip8 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")

add_executable(Chip8 main.c loader.c main.h fetcher.c decoder.c)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(Chip8 ${SDL2_LIBRARY})

//
// Created by Jasper Grant on 2023-04-13.
//

#ifndef CHIP8_MAIN_H
#define CHIP8_MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_START_ADDRESS 0x200
#define MEMORY_END_ADDRESS 4095

//Declare registers of emulator
extern char registers[16];
//Declare memory of emulator
extern char memory[4096];
//Declare index register
extern short I;
//Declare program counter
//Initializes at first available address in memory
extern short PC;
//Declare stack pointer
extern char SP;



extern void load(char *filename);

#endif //CHIP8_MAIN_H

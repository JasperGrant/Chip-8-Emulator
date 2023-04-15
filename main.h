//
// Created by Jasper Grant on 2023-04-13.
//

#ifndef CHIP8_MAIN_H
#define CHIP8_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>


#define MEMORY_START_ADDRESS 0x200
#define MEMORY_END_ADDRESS 4095

//Define macros for sections of Opcode
//Most significant nibble of opcode.
//Could not find a better name
#define MSN(x) (x>>12)
//Second nibble of opcode
#define X(x) ((x>>8)&0xf)
//Third nibble of opcode
#define Y(x) ((x>>4)&0xf)
//Fourth nibble of opcode
#define N(x) (x&0xf)
//Second byte of opcode
#define NN(x) (x&0xff)
//Second, third and fourth nibbles of opcode
#define NNN(x) (x&0xfff)

//Define enum for instructions to make errors more clear
enum instructions {
    i00E0, i00EE, i1NNN, i2NNN,
    i3XNN, i4XNN, i5XY0, i6XNN,
    i7XNN, i8XY0, i8XY1, i8XY2,
    i8XY3, i8XY4, i8XY5, i8XY6,
    i8XY7, i8XYE, i9XY0, iANNN,
    iBNNN, iCXNN, iDXYN, iEX9E,
    iEXA1, iFX07, iFX0A, iFX15,
    iFX18, iFX1E, iFX29, iFX33,
    iFX55, iFX65, unknown
};

//Declare registers of emulator
extern unsigned char registers[16];
//Declare memory of emulator
extern unsigned char memory[4096];
//Declare index register
extern unsigned short I;
//Declare program counter
//Initializes at first available address in memory
extern unsigned short PC;
//Declare stack pointer
extern unsigned char SP;

extern void load(char *filename);

extern unsigned short fetch(void);

extern enum instructions decode(unsigned short opcode);

#endif //CHIP8_MAIN_H

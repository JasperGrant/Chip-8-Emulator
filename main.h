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

//Display macros
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define PIXEL_WIDTH 10
#define PIXEL_HEIGHT 10

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

extern void execute_00E0(void);
extern void execute_00EE(void);
extern void execute_1NNN(unsigned short NNN);
extern void execute_2NNN(unsigned short NNN);
extern void execute_3XNN(unsigned char X, unsigned char NN);
extern void execute_4XNN(unsigned char X, unsigned char NN);
extern void execute_5XY0(unsigned char X, unsigned char Y);
extern void execute_6XNN(unsigned char X, unsigned char NN);
extern void execute_7XNN(unsigned char X, unsigned char NN);
extern void execute_8XY0(unsigned char X, unsigned char Y);
extern void execute_8XY1(unsigned char X, unsigned char Y);
extern void execute_8XY2(unsigned char X, unsigned char Y);
extern void execute_8XY3(unsigned char X, unsigned char Y);
extern void execute_8XY4(unsigned char X, unsigned char Y);
extern void execute_8XY5(unsigned char X, unsigned char Y);
extern void execute_8XY6(unsigned char X, unsigned char Y);
extern void execute_8XY7(unsigned char X, unsigned char Y);
extern void execute_8XYE(unsigned char X, unsigned char Y);
extern void execute_9XY0(unsigned char X, unsigned char Y);
extern void execute_ANNN(unsigned short NNN);
extern void execute_BNNN(unsigned short NNN);
extern void execute_CXNN(unsigned char X, unsigned char NN);
extern void execute_DXYN(unsigned char X, unsigned char Y, unsigned char N);
extern void execute_EX9E(unsigned char X);
extern void execute_EXA1(unsigned char X);
extern void execute_FX07(unsigned char X);
extern void execute_FX0A(unsigned char X);
extern void execute_FX15(unsigned char X);
extern void execute_FX18(unsigned char X);
extern void execute_FX1E(unsigned char X);
extern void execute_FX29(unsigned char X);
extern void execute_FX33(unsigned char X);
extern void execute_FX55(unsigned char X);
extern void execute_FX65(unsigned char X);

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
//Declare stack array
extern unsigned short stack[16];
//Declare display
extern unsigned char display[64][32];

extern void load(char *filename);

extern unsigned short fetch(void);

extern enum instructions decode(unsigned short opcode);

extern void display_init(void);

extern unsigned char draw_pixel(unsigned char x, unsigned char y);

extern void execute(unsigned short opcode, enum instructions);

#endif //CHIP8_MAIN_H

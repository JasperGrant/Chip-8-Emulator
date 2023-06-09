//Fetcher file for Chip8 Emulator Project
//Contains fetching section of FDE cycle
//Written by Jasper Grant 2023-05-01

#include "main.h"

//Function which fetches instructions
//Only a separate function to emphasize fetch,decode, execute cycle
unsigned short fetch(void){
    //Fetch opcode from memory
    unsigned char MSB = memory[PC];
    unsigned char LSB = memory[PC+1];
    //Increment program counter
    PC += 2;
    //Return instruction
    return MSB << 8 | LSB;
}

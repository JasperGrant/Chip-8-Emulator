//
// Created by Jasper Grant on 2023-04-13.
//

#include "main.h"

short fetch(void){
    //Fetch opcode from memory
    unsigned short opcode = memory[PC]<<8 & memory[PC+1];
    //Increment program counter
    PC += 2;
    //Return instruction
    return opcode;
}

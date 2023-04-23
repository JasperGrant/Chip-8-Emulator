//
// Created by Jasper Grant on 2023-04-13.
//

#include "main.h"


//TODO: Put in checks to make sure that top level paths finish in unknown instruction if incorrect
//Example: 9XY1 Will go in as a correct 9XY0
enum instructions decode(unsigned short opcode){
    switch(MSN(opcode)){
        case 0x0:
            switch(N(opcode)){
                case 0x0:
                    return i00E0;
                case 0xe:
                    return i00EE;

            }
            break;
        case 0x1:
            return i1NNN;
        case 0x2:
            return i2NNN;
        case 0x3:
            return i3XNN;
        case 0x4:
            return i4XNN;
        case 0x5:
            return i5XY0;
        case 0x6:
            return i6XNN;
        case 0x7:
            return i7XNN;
        case 0x8:
            switch(N(opcode)){
                case 0x0:
                    return i8XY0;
                case 0x1:
                    return i8XY1;
                case 0x2:
                    return i8XY2;
                case 0x3:
                    return i8XY3;
                case 0x4:
                    return i8XY4;
                case 0x5:
                    return i8XY5;
                case 0x6:
                    return i8XY6;
                case 0x7:
                    return i8XY7;
                case 0xe:
                    return i8XYE;
            }
            break;
        case 0x9:
            return i9XY0;
        case 0xa:
            return iANNN;
        case 0xb:
            return iBNNN;
        case 0xc:
            return iCXNN;
        case 0xd:
            return iDXYN;
        case 0xe:
            switch(NN(opcode)){
                case 0x9e:
                    return iEX9E;
                case 0xa1:
                    return iEXA1;
            }
            break;
        case 0xf:
            switch(NN(opcode)){
                case 0x07:
                    return iFX07;
                case 0x0A:
                    return iFX0A;
                case 0x15:
                    return iFX15;
                case 0x18:
                    return iFX18;
                case 0x1e:
                    return iFX1E;
                case 0x29:
                    return iFX29;
                case 0x33:
                    return iFX33;
                case 0x55:
                    return iFX55;
                case 0x65:
                    return iFX65;
            }
            break;
    }


    return unknown;
}
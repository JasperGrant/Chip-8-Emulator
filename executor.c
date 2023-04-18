//
// Created by Jasper Grant on 2023-04-17.
//

#include "main.h"

unsigned char SP;

unsigned short stack[16];

unsigned short I;


void execute(unsigned short opcode, enum instructions inst){
    switch (inst) {
        case i00E0:
            execute_00E0();
            break;
        case i00EE:
            execute_00EE();
            break;
        case i1NNN:
            execute_1NNN(NNN(opcode));
            break;
        case i2NNN:
            execute_2NNN(NNN(opcode));
        case i3XNN:
            execute_3XNN(X(opcode), NNN(opcode));
            break;
        case i4XNN:
            execute_4XNN(X(opcode), NNN(opcode));
            break;
        case i5XY0:
            execute_5XY0(X(opcode), Y(opcode));
            break;
        case i6XNN:
            execute_6XNN(X(opcode), NNN(opcode));
            break;
        case i7XNN:
            execute_7XNN(X(opcode), NNN(opcode));
            break;
        case i8XY0:
            execute_8XY0(X(opcode), Y(opcode));
            break;
        case i8XY1:
            execute_8XY1(X(opcode), Y(opcode));
            break;
        case i8XY2:
            execute_8XY2(X(opcode), Y(opcode));
            break;
        case i8XY3:
            execute_8XY3(X(opcode), Y(opcode));
            break;
        case i8XY4:
            execute_8XY4(X(opcode), Y(opcode));
            break;
        case i8XY5:
            execute_8XY5(X(opcode), Y(opcode));
            break;
        case i8XY6:
            execute_8XY6(X(opcode), Y(opcode));
            break;
        case i8XY7:
            execute_8XY7(X(opcode), Y(opcode));
            break;
        case i8XYE:
            execute_8XYE(X(opcode), Y(opcode));
            break;
        case i9XY0:
            execute_9XY0(X(opcode), Y(opcode));
            break;
        case iANNN:
            execute_ANNN(NNN(opcode));
            break;
        case iBNNN:
            execute_BNNN(NNN(opcode));
            break;
        case iCXNN:
            execute_CXNN(NN(opcode));
            break;
        case iDXYN:
            execute_DXYN(X(opcode), Y(opcode), N(opcode));
            break;
        case iEX9E:
            execute_EX9E(X(opcode));
            break;
        case iEXA1:
            execute_EXA1(X(opcode));
            break;
        case iFX07:
            execute_FX07(X(opcode));
            break;
        case iFX0A:
            execute_FX0A(X(opcode));
            break;
        case iFX15:
            execute_FX15(X(opcode));
            break;
        case iFX18:
            execute_FX18(X(opcode));
            break;
        case iFX1E:
            execute_FX1E(X(opcode));
            break;
        case iFX29:
            execute_FX29(X(opcode));
            break;
        case iFX33:
            execute_FX33(X(opcode));
            break;
        case iFX55:
            execute_FX55(X(opcode));
            break;
        case iFX65:
            execute_FX65(X(opcode));
            break;
        default:
            printf("Error: Unknown instruction got to execution!");
            exit(-1);

    }

}

//Execution for clear screen instruction
//CLS
void execute_00E0(void){
    //Double loop to iterate through each pixel on screen
    for(int x_counter = 0; x_counter <SCREEN_WIDTH/PIXEL_WIDTH; x_counter+=PIXEL_WIDTH){
        for(int y_counter = 0; y_counter<SCREEN_HEIGHT/PIXEL_HEIGHT; y_counter +=PIXEL_HEIGHT){
            //If a pixel is set
            if(display[x_counter][y_counter] == 1){
                //Change value in array and then unset
                display[x_counter][y_counter] = 0;
                draw_pixel(x_counter, y_counter);
            }

        }
    }
}

//Execution for return from subroutine instruction
//RET
void execute_00EE(void){
    //SP = -1 is the case where stack is empty.
    if(SP == 0){
        //may remove this if correct behavior is
        printf("Error: Nothing to return from");
    }
    else{
        //PC is filled from stack pointer
        PC = stack[SP];
        //Stack pointer is decremented
        SP--;
    }
}

//Execution of jump instruction
//JP
void execute_1NNN(unsigned short NNN){
    //Program counter is equal to final three nibbles
    PC = NNN;
}
//Execution of call subroutine instruction
//CALL addr
void execute_2NNN(unsigned short NNN){
    //If SP == 0xf
    if(SP == 15) {
        printf("Error: stack overflow");
        exit(-1);
    }
    //Increment Stack pointer
    SP++;
    //Place PC on stack
    stack[SP] = PC;
    //Set program counter to final three nibbles
    PC = NNN;

}

//Execution of skip if equal instruction
//SE Vx, byte
void execute_3XNN(unsigned char X, unsigned char NN){
    //If register Vx = NN
    if(registers[X] == NN){
        //Skip one instruction by adding 2 to PC
        PC+=2;
    }

}

//Execution of skip if not equal instruction
//SNE Vx, byte
void execute_4XNN(unsigned char X, unsigned char NN){
    //If register Vx != NN
    if(registers[X] != NN){
        //Skip one instruction by adding 2 to PC
        PC+=2;
    }
}

//Execution of skip if registers are equal instruction
//SE Vx, Vy
void execute_5XY0(unsigned char X, unsigned char Y){
    //If register Vx == Vy
    if(registers[X] == registers[Y]){
        //Skip one instruction by adding 2 to PC
        PC+=2;
    }
}

//Execution of load instruction
//LD Vx, byte
void execute_6XNN(unsigned char X, unsigned char NN){
    //Load value NN into register Vx
    registers[X] = NN;
}

//Execution of add to register instruction
//ADD Vx, byte
void execute_7XNN(unsigned char X, unsigned char NN){
    //Add value NN to register Vx
    registers[X] += NN;
}

//Execution of copy register instruction
//LD Vx, Vy
void execute_8XY0(unsigned char X, unsigned char Y){
    //Copy register to another register
    registers[X] = registers[Y];
}

//Execution of registers OR instruction
//OR Vx, Vy
void execute_8XY1(unsigned char X, unsigned char Y){
    //Set Vx = Vx OR vy
    registers[X] = registers[X] | registers[Y];
}

//Execution of registers AND instruction
//AND Vx, Vy
void execute_8XY2(unsigned char X, unsigned char Y){
    //Set Vx = Vx AND vy
    registers[X] = registers[X] & registers[Y];
}

//Execution of registers XOR instruction
//XOR Vx, Vy
void execute_8XY3(unsigned char X, unsigned char Y){
    //Set Vx = Vx XOR vy
    registers[X] = registers[X] ^ registers[Y];
}

//Execution of registers add instruction
//ADD Vx, Vy
void execute_8XY4(unsigned char X, unsigned char Y){
    /*
    //If total is greater then 256
    if(registers[X] + registers[Y]) ==
    //Set Vx to Vx + Vy
    registers[X] = registers[X] + registers[Y];
     */
}

//Execution of registers subtract instruction
//SUB Vx, Vy
void execute_8XY5(unsigned char X, unsigned char Y){}
void execute_8XY6(unsigned char X, unsigned char Y){}
void execute_8XY7(unsigned char X, unsigned char Y){}
void execute_8XYE(unsigned char X, unsigned char Y){}
void execute_9XY0(unsigned char X, unsigned char Y){}

//Execution for index load register
void execute_ANNN(unsigned short NNN){
    //Set I = NNN
    I = NNN;
}
void execute_BNNN(unsigned short NNN){}
void execute_CXNN(unsigned char NN){}

//Execution for draw instruction
void execute_DXYN(unsigned char X, unsigned char Y, unsigned char N){
    //Set Vf to 0
    registers[0xf] = 0;
    //Pull values out of registers
    //X and Y are now the values stored at registers
    //Vx and Vy
    X = registers[X];
    Y = registers[Y];
    //Declare byte to store sprites in
    unsigned char byte;
    //For N rows
    for(int y = 0; y<N; y++){
        //Pull N-1th byte out of memory
        byte = memory[I + y];
        //For bit in byte / column in row
        for(int x = 0; x<8; x++){
            if((byte & (0b10000000 >> x))){
                registers[0xF] = draw_pixel(X + x, Y + y);
            }

        }
    }





}
void execute_EX9E(unsigned char X){}
void execute_EXA1(unsigned char X){}
void execute_FX07(unsigned char X){}
void execute_FX0A(unsigned char X){}
void execute_FX15(unsigned char X){}
void execute_FX18(unsigned char X){}
void execute_FX1E(unsigned char X){}
void execute_FX29(unsigned char X){}
void execute_FX33(unsigned char X){}
void execute_FX55(unsigned char X){}
void execute_FX65(unsigned char X){}

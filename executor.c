//Executor file for Chip8 Emulator Project
//Contains execution section of FDE cycle
//Written by Jasper Grant 2023-05-01

#include "main.h"

//All imported globals explained in main.h

unsigned char SP;

unsigned short stack[16];

unsigned short I;

unsigned char delay_timer;

unsigned char sound_timer;

unsigned char keypad[16];

//Function which chooses which instruction is executed
//Based on decoding
//This method was decided on for readability and easy arguments
void execute(unsigned short opcode, enum instructions inst) {
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
            execute_8XY6(X(opcode));
            break;
        case i8XY7:
            execute_8XY7(X(opcode), Y(opcode));
            break;
        case i8XYE:
            execute_8XYE(X(opcode));
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
            execute_CXNN(X(opcode), NN(opcode));
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

//Execution functions for all instructions:

//Execution for clear screen instruction
//CLS
void execute_00E0(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    //Zero display memory
    //This was implemented as a loop but memset is cleaner and faster
    memset(display, 0, sizeof(char) * SCREEN_HEIGHT / PIXEL_HEIGHT * SCREEN_WIDTH / PIXEL_WIDTH);

}

//Execution for return from subroutine instruction
//RET
void execute_00EE(void) {
    //PC is filled from stack pointer
    PC = stack[SP];
    //Stack pointer is decremented
    SP--;
}

//Execution of jump instruction
//JP
void execute_1NNN(unsigned short NNN) {
    //Program counter is equal to final three nibbles
    PC = NNN;
}

//Execution of call subroutine instruction
//CALL addr
void execute_2NNN(unsigned short NNN) {
    //If SP == 0xf
    if (SP == 15) {
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
void execute_3XNN(unsigned char X, unsigned char NN) {
    //If register Vx = NN
    if (registers[X] == NN) {
        //Skip one instruction by adding 2 to PC
        PC += 2;
    }

}

//Execution of skip if not equal instruction
//SNE Vx, byte
void execute_4XNN(unsigned char X, unsigned char NN) {
    //If register Vx != NN
    if (registers[X] != NN) {
        //Skip one instruction by adding 2 to PC
        PC += 2;
    }
}

//Execution of skip if registers are equal instruction
//SE Vx, Vy
void execute_5XY0(unsigned char X, unsigned char Y) {
    //If register Vx == Vy
    if (registers[X] == registers[Y]) {
        //Skip one instruction by adding 2 to PC
        PC += 2;
    }
}

//Execution of load instruction
//LD Vx, byte
void execute_6XNN(unsigned char X, unsigned char NN) {
    //Load value NN into register Vx
    registers[X] = NN;
}

//Execution of add to register instruction
//ADD Vx, byte
void execute_7XNN(unsigned char X, unsigned char NN) {
    //Add value NN to register Vx
    registers[X] += NN;
}

//Execution of copy register instruction
//LD Vx, Vy
void execute_8XY0(unsigned char X, unsigned char Y) {
    //Copy register to another register
    registers[X] = registers[Y];
}

//Execution of registers OR instruction
//OR Vx, Vy
void execute_8XY1(unsigned char X, unsigned char Y) {
    //Set Vx = Vx OR vy
    registers[X] = registers[X] | registers[Y];
    //Reset Vf to 0
    registers[0xf] = 0;
}

//Execution of registers AND instruction
//AND Vx, Vy
void execute_8XY2(unsigned char X, unsigned char Y) {
    //Set Vx = Vx AND vy
    registers[X] = registers[X] & registers[Y];
    //Reset Vf to 0
    registers[0xf] = 0;
}

//Execution of registers XOR instruction
//XOR Vx, Vy
void execute_8XY3(unsigned char X, unsigned char Y) {
    //Set Vx = Vx XOR vy
    registers[X] = registers[X] ^ registers[Y];
    //Reset Vf to 0
    registers[0xf] = 0;
}

//Execution of registers add instruction
//ADD Vx, Vy
void execute_8XY4(unsigned char X, unsigned char Y) {
    //Sum should be done first to not use already added values in calculation
    //Short to ensure going over 255 is possible
    unsigned short sum = registers[X] + registers[Y];
    //If register Vx is not flag
    if (X != 0xf) {
        //Set Vx to Vx + Vy
        registers[X] = registers[X] + registers[Y];
    }

    //If total is greater then 256
    registers[0xf] = (sum > 255) ? 0x1 : 0x0;
}

//Execution of subtraction Vx - Vy instruction
//SUB Vx, Vy
void execute_8XY5(unsigned char X, unsigned char Y) {
    //Set initial difference as signed to see if borrow is necessary
    char difference = registers[X] - registers[Y];
    //If register Vx is not flag
    if (X != 0xf) {
        //Subtract Vy from Vx
        registers[X] = registers[X] - registers[Y];
    }
    //Set Vf to 1 if difference > 0 and 0 if difference < 0
    registers[0xf] = difference > 0 ? 0x01 : 0x0;
}

//Execution of shift right instruction
//SHR Vx (Vy is unused)
void execute_8XY6(unsigned char X) {
    //Store LSB of Vx in Vf
    registers[0xf] = registers[X] & 0b00000001;
    //If register Vx is not flag
    if (X != 0xf) {
        //Shift Vx right by 1
        registers[X] >>= 1;
    }
}

//Execution of subtraction Vy - Vx instruction
//SUBN Vx, Vy
void execute_8XY7(unsigned char X, unsigned char Y) {
    //If register Vx is not flag
    if (X != 0xf) {
        //Subract Vy from Vx
        registers[X] = registers[Y] - registers[X];
    }
    //Set Vf to 1 if Vy > VX and 0 if not
    registers[0xf] = registers[Y] > registers[X] ? 0x01 : 0x0;
}

//Execution of shift left instruction
//SHL Vx, Vy (Vy is unused)
void execute_8XYE(unsigned char X) {
    //Store MSB of Vx in Vf
    //Quick way to get 8th bit
    //All other bits are lost in the shift
    registers[0xf] = registers[X] >> 7;
    //If register Vx has not already been set
    if (X != 0xf) {
        //Shift Vx left
        registers[X] <<= 1;
    }
}

//Execution of set not equal instruction
//SNE Vx, Vy
void execute_9XY0(unsigned char X, unsigned char Y) {
    //If registers are not equal increment PC by 2
    if (registers[X] != registers[Y]) PC += 2;
}

//Execution for index load register
//LD I, NNN
void execute_ANNN(unsigned short NNN) {
    //Set I = NNN
    I = NNN;
}

//Execution of jump with offset instruction
//JP V0, NNN
void execute_BNNN(unsigned short NNN) {
    //Set PC to address plus offset stored in V0
    PC = NNN + registers[0x0];
}

//Execution of random number generator instruction
void execute_CXNN(unsigned char X, unsigned char NN) {
    //Generate random number
    //We only need limited randomness
    registers[X] = rand();
    //AND value with NN
    registers[X] &= NN;
}

//Execution for draw instruction
void execute_DXYN(unsigned char X, unsigned char Y, unsigned char N) {
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
    for (int y = 0; y < N; y++) {
        //Pull N-1th byte out of memory
        byte = memory[I + y];
        //For bit in byte / column in row
        for (int x = 0; x < 8; x++) {
            //If a bit is one
            if ((byte & (0b10000000 >> x))) {
                //Flip bit and if a set bit is turned off: Vf = 1
                registers[0xF] = draw_pixel(X + x, Y + y);
            }

        }
    }

}

//Execution of key pressed skip instruction
//SKP Vx
void execute_EX9E(unsigned char X) {
    //If key X is pressed
    if (keypad[registers[X]]) {
        //Increment PC
        PC += 2;
    }

}

//Execution of key not pressed skip instruction
//SKNP Vx
void execute_EXA1(unsigned char X) {
    //If key in Vx is not pressed
    if (!keypad[registers[X]]) {
        //Increment PC
        PC += 2;
    }


}

//Execution of the set get delay timer value instruction
//LD Vx, DT
void execute_FX07(unsigned char X) {
    //Set value of Vx to value of delay timer
    registers[X] = delay_timer;
}

//Execution of get key pressed instruction
//LD Vx, K
void execute_FX0A(unsigned char X) {
    //Preserve state of sound and delay timers
    unsigned char sound_timer_holder = sound_timer;
    unsigned char delay_timer_holder = delay_timer;
    //Set bool to tell whether key has been pressed
    unsigned char waiting_for_key = 1;
    //Loop through keys in keypad
    for(int i = 0; i<16;i++){
        //If key pressed found
        if(keypad[i]){
            //Stop loop
            waiting_for_key = 0;
            //Return key
            registers[X] = i;
        }
    }
    //Shamelessly stolen from https://github.com/Klairm/chip8
    //I thought this was a really cool idea to just use the already going loop

    //If bool has not been flipped
    if(waiting_for_key == 1){
        //Bring state of emulator back one instruction
        PC-=2;
        sound_timer = sound_timer_holder;
        delay_timer = delay_timer_holder;
    }

}

//Execution of the set delay timer instruction
//LD ST, Vx
void execute_FX15(unsigned char X) {
    //Set value of delay timer from Vx
    delay_timer = registers[X];
}

//Execution of the set sound timer instruction
//LD DT, Vx
void execute_FX18(unsigned char X) {
    //Set value of sound timer from Vx
    sound_timer = registers[X];
}

//Execution of add register to index instruction
//ADD I, Vx
void execute_FX1E(unsigned char X) {
    //Set I to I + Vx
    I += registers[X];
}

//Execution of select font letter instruction
//LD F, Vx
void execute_FX29(unsigned char X) {
    //Set I to the memory location of a font letter
    I = registers[X] * 5;
    //Font sprites start at 0 and each take 5 characters
}

//Execution of digit store instruction
//LD [I] Vx
void execute_FX33(unsigned char X) {
    //Stores base ten interpretation of Vx in I, I+1, I+2
    memory[I] = registers[X] / 100;
    memory[I + 1] = (registers[X] % 100) / 10;
    memory[I + 2] = registers[X] % 10;
    //It should be noted that I should not be automatically
    //incremented at the end of this function
}

//Execution of instruction to store register values in memory
//LD [I], Vx
void execute_FX55(unsigned char X) {
    //Loop from V0 to Vx
    for (int i = 0; i <= X; i++) {
        //Store ith register in I+i memory address
        memory[I + i] = registers[i];
    }
    //Increment I by number of registers
    I += (X + 1);

}

//Execution of instruction to restore register values from memory
//LD Vx, [I]
void execute_FX65(unsigned char X) {
    //Loop from V0 to Vx
    for (int i = 0; i <= X; i++) {
        //Store I+i memory address in ith register
        registers[i] = memory[I + i];
    }
}

#include "main.h"

unsigned short PC;

int main(int argc, char** argv) {

    //Load ROM
    //Switch case to error check for incorrect numbers of arguments
    switch(argc) {
        //Case with no inputs
        case 1:
            //Throw error and exit
            printf("Error: No input file!\n");
            exit(-1);
        case 2:
            //Load input file
            load(argv[1]);
            break;
        default:
            //Throw error and exit
            printf("Error: Too many arguments\n");
            exit(-1);
    }

    PC = MEMORY_START_ADDRESS;
    //FDE Loop

    //Declare opcode variable
    unsigned short opcode;
    //Declare variable to tell type of instruction
    enum instructions inst;

    while(PC < 4096) {
        //Fetch
        opcode = fetch();
        //Decode
        inst = decode(opcode);
        //Execute
        //execute(opcode, inst);
    }
}


#include "main.h"

short PC;

int main(int argc, char** argv) {

    //Load ROM
    switch(argc) {
        case 1:
            printf("Error: No input file!\n");
            exit(-1);
        case 2:
            load(argv[1]);
        default:
            printf("Error: Too many arguments\n");
    }
    PC = MEMORY_START_ADDRESS;
    //FDE Loop

        //Fetch

        //Decode

        //Execute
}

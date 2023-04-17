#include "main.h"

unsigned short PC;

int main(int argc, char** argv) {

    display_init();
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

    SDL_Event event;
    while(1) {
        //Fetch
        opcode = fetch();
        //Decode
        inst = decode(opcode);
        //Execute
        //execute(opcode, inst);

        SDL_Delay(100);
        while(SDL_PollEvent(&event)>0){
            switch(event.type){
                case SDL_QUIT:
                    exit(0);
            }
        }
    }
}

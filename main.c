#include "main.h"

unsigned short PC;

int main(int argc, char** argv) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: Failed to initialized SDL2\n");
        exit(-1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480, 0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);
    //SDL_Delay(5000);

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

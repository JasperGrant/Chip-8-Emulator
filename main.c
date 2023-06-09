//Main file for Chip8 Emulator Project
//Contains some global variables along with the main and poll functions
//Written by Jasper Grant 2023-05-01

#include "main.h"

//Global explained in main.h

unsigned short PC;

//Array which represents keyboard keys corresponding to Chip8 keys
//Mapping for these is very counter intuitive.
//It really goes by index instead of the layout you see here
unsigned char keymap[16] = {
        SDLK_x, SDLK_1, SDLK_2, SDLK_3,
        SDLK_q, SDLK_w, SDLK_e, SDLK_a,
        SDLK_s, SDLK_d, SDLK_z, SDLK_c,
        SDLK_4, SDLK_r, SDLK_f, SDLK_v,

};

//Chip 8 standard font set
unsigned char font[80] =
        {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

//Event type to handle SDL events in poll
SDL_Event event;

//Main function
int main(int argc, char **argv) {

    for (int i = 0; i < 80; ++i)
        memory[i] = font[i];

    display_init();
    //Load ROM
    //Switch case to error check for incorrect numbers of arguments
    switch (argc) {
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

    SP = -1;
    PC = MEMORY_START_ADDRESS;
    //FDE Loop

    //Declare opcode variable
    unsigned short opcode;
    //Declare variable to tell type of instruction
    enum instructions inst;

    //FDE cycle. Only stopped by exiting emulator or error.
    while (1) {
        //Fetch
        opcode = fetch();
        //Decode
        inst = decode(opcode);
        //Execute
        execute(opcode, inst);
        //Poll for keyboard events
        poll();
        //Decrement timers
        if (sound_timer) sound_timer--;
        if (delay_timer) delay_timer--;

        //Set rate here
        //Set with very small delay for testing
        SDL_Delay(1);
    }
}

//Function which polls during execution cycle for SDL events
void poll(void) {
    //Poll SDL Events
    while (SDL_PollEvent(&event)) {
        printf("%c",event.type);
        //Switch for different SDL event cases such as closing
        //the window or keypad press
        switch (event.type) {

            case SDL_QUIT:
                exit(0);
            case SDL_KEYDOWN:
                //For loop to check every key every cycle
                for (int i = 0; i <= 0xf; i++) {
                    //If a key in the map has been given by event
                    if (event.key.keysym.sym == keymap[i]){
                        //Set that keypad digit
                        keypad[i] = 1;
                    }
                }
                break;
            case SDL_KEYUP:
                for (int i = 0; i <= 0xf; i++) {
                    //If a key in the map has been given by event
                    if (event.key.keysym.sym == keymap[i]){
                        //Set that keypad digit
                        keypad[i] = 0;
                    }
                }

        }

    }

}
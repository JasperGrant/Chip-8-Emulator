#include "main.h"

unsigned short PC;

unsigned char keymap[16] = {
        SDLK_1, SDLK_2, SDLK_3, SDLK_c,
        SDLK_4, SDLK_5, SDLK_6, SDLK_d,
        SDLK_7, SDLK_8, SDLK_9, SDLK_e,
        SDLK_a, SDLK_0, SDLK_b, SDLK_f,

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

SDL_Event event;

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

    while (1) {
        //Fetch
        opcode = fetch();
        //Decode
        inst = decode(opcode);
        //Execute
        execute(opcode, inst);
        //Poll
        poll();
    }
}

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
                for (int i = 0; i < 0xf; i++) {
                    //If a key in the map has been given by event
                    if (event.key.keysym.sym == keymap[i]){
                        //Set that keypad digit
                        keypad[i] = 1;
                    }
                }
                break;
            case SDL_KEYUP:
                for (int i = 0; i < 0xf; i++) {
                    //If a key in the map has been given by event
                    if (event.key.keysym.sym == keymap[i]){
                        //Set that keypad digit
                        keypad[i] = 0;
                    }
                }

        }

    }

    //Decrement timers
    if (sound_timer) sound_timer--;
    if (delay_timer) delay_timer--;

    SDL_Delay(5);

}
//Loader file for Chip8 Emulator Project
//Contains function to load Chip8 ROMs
//Written by Jasper Grant 2023-05-01

#include "main.h"

//Imported global explained in main.h

unsigned char memory[4096];


//Function which loads ROMs. Contains error conditions for multiple
//files or no files
void load(char *filename) {

    //Attempt to open input file
    FILE *rom = fopen(filename, "rb");

    //If file exists
    if (rom != NULL) {
        //Find end of file
        fseek(rom, 0, SEEK_END);
        //rom_len is equal to the length of file
        long rom_len = ftell(rom);
        //Make buffer the size of all data in file
        rewind(rom);
        char *buffer = (char *) malloc(rom_len);
        //Read file data into buffer
        fread(buffer, sizeof(char), rom_len, rom);
        //If buffer fits in memory
        if (rom_len <= MEMORY_END_ADDRESS - MEMORY_START_ADDRESS) {
            //Loop through buffer

            for (int i = 0; i < rom_len; i++) {
                //Put all data into memory
                memory[MEMORY_START_ADDRESS + i] = buffer[i];
            }
        //Case where buffer does not fit into memory
        } else {
            //Throw error and exit
            printf("ROM file size too large!\n");
            exit(-1);
        }
    //Case where file does not exist
    } else {
        //Throw error and exit
        printf("Error: ROM does not exist!\n");
        exit(-1);
    }

}
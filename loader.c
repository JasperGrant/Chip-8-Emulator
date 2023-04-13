//
// Created by Jasper Grant on 2023-04-12.
//
#include "main.h"

char memory[4096];

void load(char *filename) {
    FILE *rom = fopen(filename, "rb");
    if (rom != NULL) {
        fseek(rom, 0, SEEK_END);
        long rom_len = ftell(rom);
        char *buffer = (char *) malloc(rom_len);
        fread(buffer, sizeof(char), rom_len, rom);

        if (rom_len <= MEMORY_END_ADDRESS - MEMORY_END_ADDRESS) {
            for (int i = 0; i < rom_len; i++) {
                memory[MEMORY_START_ADDRESS + i] = buffer[i];
            }
        } else {
            printf("ROM file size too large!\n");
            exit(-1);
        }
    } else {
        printf("Error: ROM does not exist!\n");
        exit(-1);
    }

}
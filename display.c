//
// Created by Jasper Grant on 2023-04-15.
//

#include "main.h"

//Display macros
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define PIXEL_WIDTH 10
#define PIXEL_HEIGHT 10

//Declare globals for window, renderer, and texture
//Global to be used in execution functions
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_FRect rect;

unsigned char registers[16];

unsigned char display[64][32];

void display_init(void){
    //Attempt to init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: Failed to initialized SDL2\n");
        exit(-1);
    }

    //Initialize window variable
    window = SDL_CreateWindow("Chip-8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    //Initialize renderer that draws shapes
    renderer = SDL_CreateRenderer(window, -1, 0);
    //Set height and width of pixels on screen
    rect.w = PIXEL_WIDTH;
    rect.h = PIXEL_HEIGHT;

    //Set color of pixels
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
}

void draw_pixel(unsigned char x, unsigned char y){
    //Assign values from coordinate variables to rectangle representing pixel
    rect.x = x * PIXEL_WIDTH;
    rect.y = y * PIXEL_WIDTH;

    //If this pixel is already drawn
    if(display[x][y] == 1){
        //Set color to undraw pixel
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        //Set VF to 1
        registers[0xF] = 1;
        //Set pixel to 0 in array
        display[x][y] = 0;
    }
    else{
        //Mark that a pixel has been set
        display[x][y] = 1;
    }
    SDL_RenderDrawRectF(renderer, &rect);
    SDL_RenderPresent(renderer);

    //Set color back to default regardless
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
}
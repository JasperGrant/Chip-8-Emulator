//
// Created by Jasper Grant on 2023-04-15.
//

#include "main.h"

//Declare globals for window, renderer, and texture
//Global to be used in execution functions
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

void display_init(){
    //Attempt to init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: Failed to initialized SDL2\n");
        exit(-1);
    }
    //
    window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXEL)
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
}
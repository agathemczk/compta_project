#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BOX_HEIGHT ((WINDOW_HEIGHT * 2 / 3) / 2)
#define BOX_WIDTH (WINDOW_WIDTH / 3)
#define MARGIN 10
#define BORDER_THICKNESS 5
#define OFFSET_Y 10

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("The big boxes market", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (TTF_Init() != 0) {
        printf("Error initializing TTF: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    TTF_Font* font = TTF_OpenFont("C:\\Users\\agath\\Documents\\SDL\\Baloo-Regular.ttf", 25); //à adapter
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    SDL_Rect boxes[6];
    SDL_Color colors[6] = {{160, 93, 201, 255}, {233, 131, 65, 255}, {68, 201, 110, 255}, {218, 217, 67, 255}, {237, 116, 213, 255}, {82, 113, 201, 255}};

    for(int i = 0; i < 6; i++) {
        boxes[i].w = BOX_WIDTH - 2 * MARGIN;
        boxes[i].h = BOX_HEIGHT - 2 * MARGIN;
        boxes[i].x = (i % 3) * BOX_WIDTH + MARGIN;
        boxes[i].y = (i / 3) * (BOX_HEIGHT + MARGIN) + OFFSET_Y;
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 6; i++) {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            for(int j = 0; j < BORDER_THICKNESS; j++) {
                SDL_Rect border = {boxes[i].x - j, boxes[i].y - j, boxes[i].w + 2*j, boxes[i].h + 2*j};
                SDL_RenderDrawRect(renderer, &border);
            }
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


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
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 35

typedef struct {
    int value;
} Element;


typedef struct {
    Element *elements;
    int size;
    int capacity;
} Container;

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
    SDL_Color gray = {192, 192, 192, 255};
    SDL_Color darkGray = {128, 128, 128, 255};
    SDL_Color white = {255, 255, 255, 255};

    for(int i = 0; i < 6; i++) {
        boxes[i].w = BOX_WIDTH - 2 * MARGIN;
        boxes[i].h = BOX_HEIGHT - 2 * MARGIN;
        boxes[i].x = (i % 3) * BOX_WIDTH + MARGIN;
        boxes[i].y = (i / 3) * (BOX_HEIGHT + MARGIN) + OFFSET_Y;
    }

    SDL_Rect buyButton = {WINDOW_WIDTH / 2 - BUTTON_WIDTH - BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_Rect sellButton = {WINDOW_WIDTH / 2 + BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};

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

        int x, y;
        SDL_GetMouseState(&x, &y);
        bool isBuyHovered = x >= buyButton.x && x <= buyButton.x + buyButton.w && y >= buyButton.y && y <= buyButton.y + buyButton.h;
        bool isSellHovered = x >= sellButton.x && x <= sellButton.x + sellButton.w && y >= sellButton.y && y <= sellButton.y + sellButton.h;

        SDL_SetRenderDrawColor(renderer, isBuyHovered ? darkGray.r : gray.r, isBuyHovered ? darkGray.g : gray.g, isBuyHovered ? darkGray.b : gray.b, isBuyHovered ? darkGray.a : gray.a);
        SDL_RenderFillRect(renderer, &buyButton);
        SDL_SetRenderDrawColor(renderer, isSellHovered ? darkGray.r : gray.r, isSellHovered ? darkGray.g : gray.g, isSellHovered ? darkGray.b : gray.b, isSellHovered ? darkGray.a : gray.a);
        SDL_RenderFillRect(renderer, &sellButton);

        SDL_Surface* buySurface = TTF_RenderText_Solid(font, "BUY", white);
        SDL_Texture* buyTexture = SDL_CreateTextureFromSurface(renderer, buySurface);
        int buyWidth, buyHeight;
        SDL_QueryTexture(buyTexture, NULL, NULL, &buyWidth, &buyHeight);
        SDL_Rect buyRect = {buyButton.x + (buyButton.w - buyWidth) / 2, buyButton.y + (buyButton.h - buyHeight) / 2, buyWidth, buyHeight};
        SDL_RenderCopy(renderer, buyTexture, NULL, &buyRect);

        SDL_Surface* sellSurface = TTF_RenderText_Solid(font, "SELL", white);
        SDL_Texture* sellTexture = SDL_CreateTextureFromSurface(renderer, sellSurface);
        int sellWidth, sellHeight;
        SDL_QueryTexture(sellTexture, NULL, NULL, &sellWidth, &sellHeight);
        SDL_Rect sellRect = {sellButton.x + (sellButton.w - sellWidth) / 2, sellButton.y + (sellButton.h - sellHeight) / 2, sellWidth, sellHeight};
        SDL_RenderCopy(renderer, sellTexture, NULL, &sellRect);

        SDL_RenderPresent(renderer);

        SDL_FreeSurface(buySurface);
        SDL_DestroyTexture(buyTexture);
        SDL_FreeSurface(sellSurface);
        SDL_DestroyTexture(sellTexture);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

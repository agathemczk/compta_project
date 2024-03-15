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

void handle_error(const char* message, TTF_Font* font, SDL_Renderer* renderer, SDL_Window* window) {
    printf("%s: %s\n", message, SDL_GetError());
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
    exit(1);
}

void render_button(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect button, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect rect = {button.x + (button.w - width) / 2, button.y + (button.h - height) / 2, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

//structure d'un objet
typedef struct object {
    struct object* next;
} object;

//structure d'une boîte, avec son numéro et le count d'objets qu'elle contient
typedef struct box {
    int number_of_the_box;
    int count_of_objects;
    object* firstobject;
} box;

//Pour ajouter des objets à une boîte
void add_object (box* box) {
    object* new_object = (object*)malloc(sizeof(object));
    new_object->next = box->firstobject;
    box->firstobject = new_object;
    box->count_of_objects++;
}

//Pour supprimer des objets d'une boîte
void delete_object (box* box) {
    if (box->firstobject != NULL) {
        object* next_object = box->firstobject->next;
        free(box->firstobject);
        box->firstobject = next_object;
        box->count_of_objects--;
    }
}

// Function to display a blue square in the middle of the selected box
void BuySomething(SDL_Renderer* renderer, int selectedBox, SDL_Rect* boxes) {
    if (selectedBox >= 0 && selectedBox < 6) {
        SDL_Rect blue_square = {boxes[selectedBox].x + (boxes[selectedBox].w - 20) / 2, boxes[selectedBox].y + (boxes[selectedBox].h - 20) / 2, 20, 20};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &blue_square);
    }
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        handle_error("Error initializing SDL", NULL, NULL, NULL);
    }

    SDL_Window* window = SDL_CreateWindow("Thebig boxes market", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        handle_error("Error creating window", NULL, NULL, NULL);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        handle_error("Error creating renderer", NULL, NULL, window);
    }

    if (TTF_Init() != 0) {
        handle_error("Error initializing TTF", NULL, renderer, window);
    }

    TTF_Font* font = TTF_OpenFont("C:\\Users\\coren\\OneDrive\\Documents\\Cours\\Programmation\\git\\compta_project\\Baloo-Regular.ttf", 25);
    if (font == NULL) {
        handle_error("Error loading font", font, renderer, window);
    }

    //Créer les boîtes
    box boxes[6];
    for(int i = 0; i < 6; i++) {
        boxes[i].number_of_the_box = i;
        boxes[i].count_of_objects = 0;
        boxes[i].firstobject = NULL;
    }

    SDL_Rect boxRects[6];
    SDL_Color colors[6] = {{160, 93, 201, 255}, {233, 131, 65, 255}, {68, 201, 110, 255}, {218, 217, 67, 255}, {237, 116, 213, 255}, {82, 113, 201, 255}};
    SDL_Color gray = {192, 192, 192, 255};
    SDL_Color darkGray = {128, 128, 128, 255};

    for(int i = 0; i < 6; i++) {
        boxRects[i].w = BOX_WIDTH - 2 * MARGIN;
        boxRects[i].h = BOX_HEIGHT - 2 * MARGIN;
        boxRects[i].x = (i % 3) * BOX_WIDTH + MARGIN;
        boxRects[i].y = (i / 3) * (BOX_HEIGHT + MARGIN) + OFFSET_Y;
    }

    SDL_Rect buyButton = {WINDOW_WIDTH / 2 - BUTTON_WIDTH - BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_Rect sellButton = {WINDOW_WIDTH / 2 + BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};

    bool running = true;
    int selectedBox = -1; // Initialize selected box to -1
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON_LEFT) {
                    if(event.button.x >= buyButton.x && event.button.x <= buyButton.x + buyButton.w && event.button.y >= buyButton.y && event.button.y <= buyButton.y + buyButton.h) {
                        selectedBox = -1; // Reset selected box when pressing "buy"
                    } else if (selectedBox >= 0 && selectedBox < 6) {
                        // User clicked on a box
                        BuySomething(renderer, selectedBox, boxRects);
                    } else {
                        // Check if the user clicked on a box
                        for(int i = 0; i < 6; i++) {
                            if(event.button.x >= boxRects[i].x && event.button.x <= boxRects[i].x + boxRects[i].w && event.button.y >= boxRects[i].y && event.button.y <= boxRects[i].y + boxRects[i].h) {
                                selectedBox = i;
                                break;
                            } else {
                                selectedBox = -1;
                            }
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 6; i++) {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            for(int j = 0; j < BORDER_THICKNESS; j++) {
                SDL_Rect border = {boxRects[i].x - j, boxRects[i].y - j, boxRects[i].w + 2*j, boxRects[i].h + 2*j};
                SDL_RenderDrawRect(renderer, &border);
            }
        }

        int x, y;
        SDL_GetMouseState(&x, &y);
        bool isBuyHovered = x >= buyButton.x && x <= buyButton.x + buyButton.w && y >= buyButton.y && y <= buyButton.y + buyButton.h;
        bool isSellHovered = x >= sellButton.x && x <= sellButton.x + sellButton.w && y >= sellButton.y && y <= sellButton.y + sellButton.h;

        SDL_Color white = {255, 255, 255, 255};
        render_button(renderer, font, "BUY", buyButton, isBuyHovered ? darkGray : gray);
        render_button(renderer, font, "SELL", sellButton, isSellHovered ? darkGray : gray);

        // Check if the user clicked on a box
        for(int i = 0; i < 6; i++) {
            if (selectedBox == i) {
                SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 128); // Partially transparent color for the selected box
                SDL_RenderFillRect(renderer, &boxRects[i]);
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

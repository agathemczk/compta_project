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
#define RED_OBJECT_SIZE 25
#define MARGIN_BETWEEN_OBJECTS 14

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
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect rect = {button.x + (button.w - width) / 2, button.y + (button.h - height) / 2, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void render_button_background(SDL_Renderer* renderer, SDL_Rect button, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &button);
}

void render_boxes(SDL_Renderer* renderer, SDL_Rect* boxes, SDL_Color* colors, int border_thickness) {
    for(int i = 0; i < 6; i++) {
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        for(int j = 0; j < border_thickness; j++) {
            SDL_Rect border = {boxes[i].x - j, boxes[i].y - j, boxes[i].w + 2*j, boxes[i].h + 2*j};
            SDL_RenderDrawRect(renderer, &border);
        }
    }
}

bool is_mouse_over(SDL_Rect button) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h);
}

void update_button_hover(SDL_Rect buyButton, SDL_Rect sellButton, bool* isBuyHovered, bool* isSellHovered) {
    *isBuyHovered = is_mouse_over(buyButton);
    *isSellHovered = is_mouse_over(sellButton);
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
bool add_object (box* box) {
    int max_objects = (BOX_WIDTH - 2 * MARGIN) / (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS) * (BOX_HEIGHT - 2 * MARGIN) / (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS);
    if (box->count_of_objects >= max_objects) {
        // La boîte est pleine
        return false;
    }
    object* new_object = (object*)malloc(sizeof(object));
    new_object->next = box->firstobject;
    box->firstobject = new_object;
    box->count_of_objects++;
    return true;
}

//Pour supprimer des objets d'une boîte
void delete_object (box* box) {
    if (box->firstobject != NULL) {
        if (box->firstobject->next == NULL) {
            free(box->firstobject);
            box->firstobject = NULL;
        } else {
            object* current_object = box->firstobject;
            while (current_object->next->next != NULL) {
                current_object = current_object->next;
            }
            free(current_object->next);
            current_object->next = NULL;
        }
        box->count_of_objects--;
    }
}

// Dessine les objets
void render_objects_in_boxes(SDL_Renderer* renderer, box* boxes, SDL_Rect* box_rects) {
    SDL_Color red = {255, 0, 0, 255};
    for(int i = 0; i < 6; i++) {
        object* current_object = boxes[i].firstobject;
        int j = 0;
        int count = 0; // Compte le nombre d'objets qui peuvent être dessinés dans la boîte
        while (current_object != NULL) {
            int column = j % ((BOX_WIDTH - 2 * MARGIN) / (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS)); // Numéro de colonne
            int row = j / ((BOX_WIDTH - 2 * MARGIN) / (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS)); // Numéro de ligne
            SDL_Rect object_rect = {
                    box_rects[i].x + MARGIN_BETWEEN_OBJECTS + column * (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS),
                    box_rects[i].y + MARGIN_BETWEEN_OBJECTS + row * (RED_OBJECT_SIZE + MARGIN_BETWEEN_OBJECTS),
                    RED_OBJECT_SIZE,
                    RED_OBJECT_SIZE
            };
            if (object_rect.y + object_rect.h <= box_rects[i].y + box_rects[i].h) {
                // L'objet ne dépasse pas de la boîte
                SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
                SDL_RenderFillRect(renderer, &object_rect);
                count++; // Incrémente le compteur
            }
            current_object = current_object->next;
            j++;
        }
        boxes[i].count_of_objects = count; // Met à jour le compteur d'objets de la boîte
    }
}




int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        handle_error("Error initializing SDL", NULL, NULL, NULL);
    }

    SDL_Window* window = SDL_CreateWindow("The big boxes market", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

    TTF_Font* font = TTF_OpenFont("C:\\Users\\agath\\Documents\\SDL\\Baloo-Regular.ttf", 25); //à adapter
    if (font == NULL) {
        handle_error("Error loading font", font, renderer, window);
    }

    bool isBuyHovered = false;
    bool isSellHovered = false;


    //Créer les boîtes
    box boxes[6];
    for(int i = 0; i < 6; i++) {
        boxes[i].number_of_the_box = i;
        boxes[i].count_of_objects = 0;
        boxes[i].firstobject = NULL;
    }

    SDL_Rect box_rects[6];
    SDL_Color colors[6] = {{160, 93, 201, 255}, {233, 131, 65, 255}, {68, 201, 110, 255}, {218, 217, 67, 255}, {237, 116, 213, 255}, {82, 113, 201, 255}};
    SDL_Color gray = {192, 192, 192, 255};
    SDL_Color darkGray = {128, 128, 128, 255};

    for(int i = 0; i < 6; i++) {
        box_rects[i].w = BOX_WIDTH - 2 * MARGIN;
        box_rects[i].h = BOX_HEIGHT - 2 * MARGIN;
        box_rects[i].x = (i % 3) * BOX_WIDTH + MARGIN;
        box_rects[i].y = (i / 3) * (BOX_HEIGHT + MARGIN) + OFFSET_Y;
    }

    SDL_Rect buyButton = {WINDOW_WIDTH / 2 - BUTTON_WIDTH - BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_Rect sellButton = {WINDOW_WIDTH / 2 + BUTTON_MARGIN / 2, WINDOW_HEIGHT * 2 / 3 + (WINDOW_HEIGHT / 3 - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};

    //test test
    for (int i = 0; i < 25; ++i) {
        add_object(&boxes[2]);
    }

    delete_object(&boxes[1]);
    add_object(&boxes[1]);

    printf("%d\n", boxes[2].count_of_objects);
    delete_object(&boxes[2]);
    delete_object(&boxes[2]);
    printf("%d\n", boxes[2].count_of_objects);


    bool running = true;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        update_button_hover(buyButton, sellButton, &isBuyHovered, &isSellHovered);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        render_boxes(renderer, box_rects, colors, BORDER_THICKNESS);

        render_button_background(renderer, buyButton, isBuyHovered ? darkGray : gray);
        render_button(renderer, font, "BUY", buyButton, isBuyHovered ? darkGray : gray);

        render_button_background(renderer, sellButton, isSellHovered ? darkGray : gray);
        render_button(renderer, font, "SELL", sellButton, isSellHovered ? darkGray : gray);

        render_objects_in_boxes(renderer, boxes, box_rects);

        SDL_RenderPresent(renderer);

    }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

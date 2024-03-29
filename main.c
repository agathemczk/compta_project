#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
#define RED_OBJECT_SIZE 25
=======
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96
#define MARGIN_BETWEEN_OBJECTS 14
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb

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

<<<<<<< HEAD
=======
void render_button_background(SDL_Renderer* renderer, SDL_Rect button, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &button);
}

<<<<<<< HEAD
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb
void render_boxes(SDL_Renderer* renderer, SDL_Rect* boxes, SDL_Color* colors, int border_thickness) {
    for(int i = 0; i < 6; i++) {
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        for(int j = 0; j < border_thickness; j++) {
            SDL_Rect border = {boxes[i].x - j, boxes[i].y - j, boxes[i].w + 2*j, boxes[i].h + 2*j};
            SDL_RenderDrawRect(renderer, &border);
        }
    }
}

<<<<<<< HEAD
=======
=======
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96
bool is_mouse_over(SDL_Rect button) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h);
}

void update_button_hover(SDL_Rect buyButton, SDL_Rect sellButton, bool* isBuyHovered, bool* isSellHovered) {
    *isBuyHovered = is_mouse_over(buyButton);
    *isSellHovered = is_mouse_over(sellButton);
}

typedef struct type_of_object {
    const char* name;
    SDL_Color color;
    int size;
} type_of_object;

type_of_object APPLE = {"Apple", {203, 65, 36, 255}, 25}; //nom, couleur, taille
type_of_object KIWI = {"Kiwi", {36, 203, 120, 255}, 20};
type_of_object BANANA = {"Banana", {215, 211, 50, 255}, 15};
type_of_object STRAWBERRY = {"Strawberry", {255, 136, 166, 255}, 10};
type_of_object IPAD = {"Ipad", {183, 154, 161, 255}, 35};

<<<<<<< HEAD
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb
//structure d'un objet
=======
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96
typedef struct object {
    type_of_object* type;
    struct object* next;
} object;

typedef struct box {
    int number_of_the_box;
    int count_of_objects;
    object* firstobject;
} box;


int max_objects_in_box(type_of_object* type) {
    return (int)((BOX_WIDTH - 2 * MARGIN) / (type->size + MARGIN_BETWEEN_OBJECTS) + 0.5) * (int)((BOX_HEIGHT - 2 * MARGIN) / (type->size + MARGIN_BETWEEN_OBJECTS) + 0.5);
}

bool add_object (box* box, type_of_object* type) {
    int max_objects = max_objects_in_box(type);
    if (box->count_of_objects >= max_objects) {
        return false;
    }
    else {
        object* new_object = (object*)malloc(sizeof(object));
        new_object->type = type;
        new_object->next = box->firstobject;
        box->firstobject = new_object;
        box->count_of_objects++;
        return true;
    }
}

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

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> e914cbc709f7c60b1f4815aaa68521c44465a662

typedef struct {
    int value;
} Element;


typedef struct {
    Element *elements;
    int size;
    int capacity;
<<<<<<< HEAD

} Container;

void buyProduct(Container *container, int quantity) {
    //voir si le conteneur a de place pr stocker nvll quantité
    if (container->size + quantity > container->capacity) {
        // Si le conteneur n'a pas assez d'espace
        container->capacity += quantity;
        container->elements = (Element *) realloc(container->elements, container->capacity * sizeof(Element));
        if (container->elements == NULL) {
            perror("Failed to reallocate memory for elements");
            exit(EXIT_FAILURE);
        }
        // Ajoute la quantité spécifiée au conteneur
        for (int i = 0; i < quantity; i++) {
            container->elements[container->size + i].value = 1; //  ajuster(taillr) selon nos besoins
        }
        container->size += quantity;
    }
}
void sellProduct(Container *container, int quantity) {
    // Vérifie si le conteneur a suffisamment d'éléments pour effectuer la vente
    if (container->size >= quantity) {
        container->size -= quantity;
    } else {
        // Gérer dans le cas où c'est insufissant élements à vendre
        printf("Not enough elements to sell %d units.\n", quantity);
    }
}
//fonction pour  liberer memoire allouer
void freeContainer(Container *container) {
    free(container->elements);
    container->size = 0;
    container->capacity = 0;
}


int main(){


    return 0;
}


=======
} Container;

>>>>>>> Stashed changes
=======
// Dessine les objets
void render_objects_in_boxes(SDL_Renderer* renderer, box* boxes, SDL_Rect* box_rects) {
    SDL_Color red = {255, 0, 0, 255};
=======
//void delete_object (box* box) {
//    if (box->firstobject != NULL) {
//        object* to_delete = box->firstobject;
//        box->firstobject = box->firstobject->next;
//        free(to_delete);
//        box->count_of_objects--;
//    }
//}

void render_boxes(SDL_Renderer* renderer, SDL_Rect* boxes, SDL_Color* colors, int border_thickness) {
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96
    for(int i = 0; i < 6; i++) {
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        for(int j = 0; j < border_thickness; j++) {
            SDL_Rect border = {boxes[i].x - j, boxes[i].y - j, boxes[i].w + 2*j, boxes[i].h + 2*j};
            SDL_RenderDrawRect(renderer, &border);
        }
    }
}


void render_objects_in_boxes(SDL_Renderer* renderer, box* boxes, SDL_Rect* box_rects) {
    for(int i = 0; i < 6; i++) {
        if (boxes[i].firstobject == NULL) {
            continue;
        }
        int max_objects = max_objects_in_box(boxes[i].firstobject->type);
        object* current_object = boxes[i].firstobject;
        int count = 0;
        while (current_object != NULL && count < max_objects) {
            int column = count % ((BOX_WIDTH - 2 * MARGIN) / (current_object->type->size + MARGIN_BETWEEN_OBJECTS));
            int row = count / ((BOX_WIDTH - 2 * MARGIN) / (current_object->type->size + MARGIN_BETWEEN_OBJECTS));
            int x = column * (current_object->type->size + MARGIN_BETWEEN_OBJECTS) + MARGIN;
            int y = row * (current_object->type->size + MARGIN_BETWEEN_OBJECTS) + MARGIN;
            int px = x + box_rects[i].x;
            int py = y + box_rects[i].y;
            SDL_Rect object_rect = {px, py, current_object->type->size, current_object->type->size};
            if (object_rect.y + object_rect.h <= box_rects[i].y + box_rects[i].h) {
                SDL_SetRenderDrawColor(renderer, current_object->type->color.r, current_object->type->color.g, current_object->type->color.b, current_object->type->color.a);
                SDL_RenderFillRect(renderer, &object_rect);
                count++;
            }
            current_object = current_object->next;
        }
    }
}


>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb
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

    TTF_Font* font = TTF_OpenFont("C:\\Users\\agath\\Documents\\SDL\\Baloo-Regular.ttf", 25);
    if (font == NULL) {
        handle_error("Error loading font", font, renderer, window);
    }

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
    bool isBuyHovered = false;
    bool isSellHovered = false;

<<<<<<< HEAD
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb

>>>>>>> 2d2e5f6a142ab97d47904a240f547cde897df314
    //Créer les boîtes
=======
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96
    box boxes[6];
    for(int i = 0; i < 6; i++) {
        boxes[i].number_of_the_box = i;
        boxes[i].count_of_objects = 0;
        boxes[i].firstobject = NULL;
    }

<<<<<<< HEAD
=======
>>>>>>> Stashed changes
    SDL_Rect boxes[6];
=======
    SDL_Rect box_rects[6];
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb
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

//LES TESTS ICI
    add_object(&boxes[2], &APPLE);
    add_object(&boxes[2], &APPLE);
    printf("%d\n", boxes[2].count_of_objects);

    add_object(&boxes[4], &STRAWBERRY);
    add_object(&boxes[4], &STRAWBERRY);
    add_object(&boxes[4], &STRAWBERRY);

    add_object(&boxes[0],&IPAD);
    add_object(&boxes[1],&KIWI);

    add_object(&boxes[5],&STRAWBERRY);


    for (int i = 0; i < 6; ++i) {
        add_object(&boxes[4], &BANANA);
    }
    printf("%d\n", boxes[4].count_of_objects);

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

<<<<<<< HEAD
        render_boxes(renderer, boxes, colors, BORDER_THICKNESS);
=======
        render_boxes(renderer, box_rects, colors, BORDER_THICKNESS);
>>>>>>> 3a3d4c74a8dc9adc8d7646e71514847459a9f5bb

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
<<<<<<< HEAD
}
<<<<<<< Updated upstream
=======
>>>>>>> e914cbc709f7c60b1f4815aaa68521c44465a662
>>>>>>> Stashed changes
=======
}
>>>>>>> f3171d16a9c732fd649c37193012ab1a0e0dec96

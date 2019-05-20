#include <stdlib.h>
#include "button.h"
#include "SDL2/SDL_image.h"


Button* newButton() {
    return (Button*) malloc(sizeof(Button));
}

void initButton(Button* b, int id, int x, int y) {
    b->buttonID = malloc(sizeof(int));
    b->absX = malloc(sizeof(int));
    b->absY = malloc(sizeof(int));
    b->width = malloc(sizeof(int));
    b->height = malloc(sizeof(int));
    b->needsUpdate = malloc(sizeof(int));
    b->isVisible = malloc(sizeof(int));

    *(b->buttonID) = id;
    *(b->absX) = x;
    *(b->absY) = y;


    *(b->width) = 0;
    *(b->height) = 0;

    *(b->needsUpdate) = 1;
    *(b->isVisible) = 1;
}

void deleteButton(Button* b) {
    free(b->buttonID);
    free(b->absX);
    free(b->absY);
    free(b->width);
    free(b->height);
    free(b->needsUpdate);
    free(b->isVisible);
    //free(b);
}

char* getImagePath(Button* b) {
    switch (*(b->buttonID)) {
        case 0:
            return "gfx/assets/buttons/enter.png";
        default:
            return "gfx/assets/buttons/exit.png";
    }
}

void renderButton(Button* b, SDL_Renderer* renderer) {
    if (*(b->needsUpdate)&&*(b->isVisible)) {
        SDL_Surface* buttonSurface;
        buttonSurface = IMG_Load(getImagePath(b));
        *(b->width) = buttonSurface->w;
        *(b->height) = buttonSurface->h;
        SDL_Rect buttonRect = {*(b->absX),*(b->absY),*(b->width),*(b->height)};
        SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer,buttonSurface);
        SDL_FreeSurface(buttonSurface);
        SDL_RenderCopy(renderer,buttonTexture,NULL,&buttonRect);
        SDL_DestroyTexture(buttonTexture);
        //*(b->needsUpdate) = 0;
    }
}

void clickButton(Button* b) {
    printf("clicked button %d\n",*(b->buttonID));
}

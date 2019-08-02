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
    b->imageLoaded = malloc(sizeof(int));

    *(b->buttonID) = id;
    *(b->absX) = x;
    *(b->absY) = y;


    *(b->width) = 0;
    *(b->height) = 0;

    *(b->needsUpdate) = 1;
    *(b->isVisible) = 1;
    *(b->imageLoaded) = 0;
}


void deleteButton(Button* b) {
    free(b->buttonID);
    free(b->absX);
    free(b->absY);
    free(b->width);
    free(b->height);
    free(b->needsUpdate);
    free(b->isVisible);
    if (*(b->imageLoaded))
        SDL_DestroyTexture(b->buttonImage);
    free(b->imageLoaded);
    //free(b);
}

char* getImagePath(Button* b) {
    switch (*(b->buttonID)) {
        case 0:
            return "data/assets/buttons/enter.png";
        case 1:
            return "data/assets/buttons/exit.png";
        case 2:
            return "data/assets/buttons/logout.png";
        default:
            return "data/assets/buttons/enter.png";
    }
}

void renderButton_old(Button* b, SDL_Renderer* renderer) {
    if (b==NULL)
        return;
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

void renderButton(Button* b, SDL_Renderer* r) {
    SDL_Rect buttonRect = {*(b->absX),*(b->absY),*(b->width),*(b->height)};
    SDL_RenderCopy(r,b->buttonImage,NULL,&buttonRect);
}

int clickButton(Button* b, int clickX, int clickY) {
    if (clickX>=*(b->absX) && clickX <= (*(b->absX)+*(b->width))
        && clickY>=*(b->absY) && clickY<=(*(b->absY)+*(b->height))) {
            return 1;
    }
    return 0;
}

void loadButtonImage(Button* b, SDL_Renderer* r) {
    char* fileName = malloc(5+strlen("data/assets/buttons/.png"));
    char* buttonNum = malloc(5);
    sprintf(buttonNum,"%d",*(b->buttonID));
    strcpy(fileName,"data/assets/buttons/");
    strcat(fileName,buttonNum);
    strcat(fileName,".png");
    SDL_Surface* buttonSurf = IMG_Load(fileName);
    *(b->width) = buttonSurf->w;
    *(b->height) = buttonSurf->h;
    b->buttonImage = SDL_CreateTextureFromSurface(r,buttonSurf);
    SDL_FreeSurface(buttonSurf);
    free(buttonNum);
    free(fileName);
    *(b->imageLoaded) = 1;
}

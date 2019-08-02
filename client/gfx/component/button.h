#ifndef H_BUTTON
#define H_BUTTON
#include "SDL2/SDL.h"

#define BUTTON_SETTINGS_INDEX 50

#define BUTTON_INFOBOX_INDEX 70

typedef struct {
    int * buttonID;
    int * absX;
    int * absY;
    int * width;
    int * height;
    int * needsUpdate;
    int * isVisible;
    int * imageLoaded;
    SDL_Texture* buttonImage;
} Button;
Button* newButton();
void initButton(Button* b, int id, int x, int y);
void deleteButton(Button* b);
char* getImagePath(Button * b);
void renderButton_old(Button* b, SDL_Renderer* renderer);
void renderButton(Button* b, SDL_Renderer* renderer);
int clickButton(Button* b, int clickX, int clickY);
void loadButtonImage(Button* b, SDL_Renderer* r);
#endif

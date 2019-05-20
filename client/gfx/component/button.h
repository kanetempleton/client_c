#ifndef H_BUTTON
#define H_BUTTON
#include "SDL2/SDL.h"
typedef struct {
    int * buttonID;
    int * absX;
    int * absY;
    int * width;
    int * height;
    int * needsUpdate;
    int * isVisible;
} Button;
Button* newButton();
void initButton(Button* b, int id, int x, int y);
void deleteButton(Button* b);
char* getImagePath(Button * b);
void renderButton(Button* b, SDL_Renderer* renderer);
void clickButton(Button* b);
#endif

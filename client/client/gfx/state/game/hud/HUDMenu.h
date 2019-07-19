#ifndef H_HUDMENU
#define H_HUDMENU
#include "SDL2/SDL.h"
#include "../../../component/button.h"

#define MAX_MENU_BUTTONS 30
#define MENU_DATA_SLOTS 50

typedef struct {
    int* menuID;
    int* numButtons;
    int* numDataSlots;
    Button* menuButton[MAX_MENU_BUTTONS];
    int* menuData[MENU_DATA_SLOTS];
} HUDMenu;

HUDMenu* newHUDMenu();
void deleteHUDMenu(HUDMenu* men);
void initHUDMenu(HUDMenu* men, int id);
void renderHUDMenu(HUDMenu* men, SDL_Renderer* r);
void processClicks_HUDMenu(HUDMenu* men, int clickX, int clickY);
#endif

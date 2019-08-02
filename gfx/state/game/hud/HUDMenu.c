#include "HUDMenu.h"
#include <stdlib.h>
#include "menus/SettingsMenu.h"
#include "HUD.h"

HUDMenu* newHUDMenu() {
    return (HUDMenu*)malloc(sizeof(HUDMenu));
}

void initHUDMenu(HUDMenu* men, int id) {
    men->menuID = malloc(sizeof(int));
    *(men->menuID) = id;
    men->numButtons = malloc(sizeof(int));
    *(men->numButtons) = 0;
    men->numDataSlots = malloc(sizeof(int));
    *(men->numDataSlots) = 0;
    for (int i=0; i<MAX_MENU_BUTTONS; i++) {
        men->menuButton[i] = newButton();
        //still need to init buttons
    }
    for (int i=0; i<MENU_DATA_SLOTS; i++) {
        men->menuData[i] = malloc(sizeof(int));
        *(men->menuData[i])=-1;
    }
}

void deleteHUDMenu(HUDMenu* men) {
    free(men->menuID);
}

void renderHUDMenu(HUDMenu* men, SDL_Renderer* r) {
    switch (*(men->menuID)) {
        case SETTINGS_MENU_ID:
            renderSettingsMenu(men,r);
            break;
    }
}

void processClicks_HUDMenu(HUDMenu* men, int clickX, int clickY) {
    switch (*(men->menuID)) {

    }
}

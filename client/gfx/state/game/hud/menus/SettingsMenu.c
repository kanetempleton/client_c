#include "SettingsMenu.h"
#include <stdlib.h>
#include "../HUD.h"
#include "../../cpanel/CPanel.h"
#include "../../../../GUI.h"
#include "../../GameState.h"

void openSettingsMenu(HUDMenu* men) {
    for (int i=0; i<NUM_BUTTONS_SETTINGS; i++) {
        int id = BUTTON_SETTINGS_INDEX+i;
        initButton(men->menuButton[i],id,settingsButtonX(id),settingsButtonY(id));
        loadButtonImage(men->menuButton[i],Main_Renderer);
    }
}

int settingsButtonX(int id) {
    switch (id) {
        case BUTTON_SETTINGS_INDEX: //map editor
            return MAP_EDIT_X;
    }
    return 0;
}

int settingsButtonY(int id) {
    switch (id) {
        case BUTTON_SETTINGS_INDEX:
            return MAP_EDIT_Y;
    }
    return 0;
}


void renderSettingsMenu(HUDMenu* men, SDL_Renderer* r) {
    for (int i=0; i<NUM_BUTTONS_SETTINGS; i++) {
        renderButton(men->menuButton[i],r);
    }
}

void processClicks_Settings(HUDMenu* men, int clickX, int clickY) {
    for (int i=0; i<NUM_BUTTONS_SETTINGS; i++) {
        if (clickButton(men->menuButton[i],clickX,clickY))
            processButtons_Settings(men,i);
    }
}

void processButtons_Settings(HUDMenu* men, int id) {
    switch (id) {
        case 0: //map editor
            if (*(men->menuData[SETTINGS_MAP_EDIT])) {
                printf("data was %d\n",*(men->menuData[SETTINGS_MAP_EDIT]));
                *(men->menuData[SETTINGS_MAP_EDIT]) = 0;
                *(yourSettings->mapEditMode) = 0;
                printf("map editing disabled\n");
            }
            else {
                *(men->menuData[SETTINGS_MAP_EDIT]) = 1;
                printf("map editing enabled\n");
                *(yourSettings->mapEditMode) = 1;
                setControlPanelState(gameCPanel,CPANEL_STATE_MAPEDIT);
            }
            break;
    }
}


void initSettingsMenu(HUDMenu* men) {
    *(men->menuData[SETTINGS_MAP_EDIT]) = 0; //disable map editing by default
    printf("init %d\n",*(men->menuData[SETTINGS_MAP_EDIT]) );
}

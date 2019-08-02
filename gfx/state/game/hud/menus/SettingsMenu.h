#ifndef H_SETTINGSMENU
#define H_SETTINGSMENU
#include "../HUDMenu.h"
#include "SDL2/SDL.h"

#define NUM_BUTTONS_SETTINGS 1
#define NUM_DATA_SLOTS_SETTINGS 5

//screen coordinates of buttons
#define MAP_EDIT_X 464
#define MAP_EDIT_Y 90

//stuff
#define SETTINGS_MAP_EDIT 0

void initSettingsMenu(HUDMenu* men);
void openSettingsMenu(HUDMenu* men);
int settingsButtonX(int id);
int settingsButtonY(int id);
void renderSettingsMenu(HUDMenu* men, SDL_Renderer* r);
void processClicks_Settings(HUDMenu* men, int clickX, int clickY);
void processButtons_Settings(HUDMenu* men, int id);
#endif

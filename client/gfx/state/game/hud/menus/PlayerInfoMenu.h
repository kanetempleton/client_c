#ifndef H_PLAYERINFOMENU
#define H_PLAYERINFOMENU
#include "../HUDMenu.h"
#include "SDL2/SDL.h"

void initPlayerInfoMenu(HUDMenu* men);
void openPlayerInfoMenu(HUDMenu* men);
void renderPlayerInfoMenu(HUDMenu* men, SDL_Renderer* r);
void processClicks_PlayerInfo(HUDMenu* men, int clickX, int clickY);
void processButtons_PlayerInfo(HUDMenu* men, int id);
#endif

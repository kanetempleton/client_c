#ifndef H_MAPEDITOR
#define H_MAPEDITOR
#include "SDL2/SDL.h"
#include "../CPanel.h"

#define MAPEDITOR_NUM_BUTTONS 3

void renderMapEditor(ControlPanel* pan, TTF_Font* font, SDL_Renderer* r);
void displayInputTileField(ControlPanel* pan);
void processCpanelClick_MapEditor(ControlPanel* pan, int button);
void searchTile(ControlPanel* pan);
#endif

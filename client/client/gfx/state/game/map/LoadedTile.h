#ifndef H_LOADEDTILE
#define H_LOADEDTILE
#include "SDL2/SDL.h"
typedef struct {
    char* tileData;
    SDL_Texture* tileTexture;
} LoadedTile;
LoadedTile* newLoadedTile();
void initLoadedTile(LoadedTile* t, SDL_Renderer* ren);
void loadDataToTile(LoadedTile* t, char* tileData, SDL_Renderer* rend);
void clearDataFromTile(LoadedTile* t);
void deleteLoadedTile(LoadedTile* t);
void renderTile(LoadedTile* t, SDL_Renderer* r, int x, int y);
#endif

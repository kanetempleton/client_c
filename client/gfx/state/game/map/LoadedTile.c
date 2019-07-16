#include "LoadedTile.h"
#include "SDL2/SDL_image.h"
#include "Map.h"
#include <string.h>
#include <stdlib.h>

LoadedTile* newLoadedTile() {
    return (LoadedTile*)malloc(sizeof(LoadedTile));
}
void initLoadedTile(LoadedTile* t, SDL_Renderer* ren) {
    t->tileData = malloc(4);
    for (int i=0; i<3; i++)
        *(t->tileData+i)='0';
    *(t->tileData+3)='\0';
    SDL_Surface* tileSurface = IMG_Load("data/assets/map/000.png");
    t->tileTexture = SDL_CreateTextureFromSurface(ren,tileSurface);
    SDL_FreeSurface(tileSurface);
}
void loadDataToTile(LoadedTile* t, char* tiledat, SDL_Renderer* rend) {
    if (strcmp(t->tileData,tiledat)==0)
        return; //dont load the image if it's already loaded
    SDL_DestroyTexture(t->tileTexture);
    for (int i=0; i<3; i++)
        *(t->tileData+i)=tiledat[i];
    *(t->tileData+3)='\0';
    char* filepath = malloc(strlen("data/assets/map/.png")+TILE_DATA_SIZE+strlen(t->tileData)+8);
    strcpy(filepath,"data/assets/map/");
    strcat(filepath,t->tileData);
    strcat(filepath,".png");
    SDL_Surface* tileSurf = IMG_Load(filepath);
    t->tileTexture = SDL_CreateTextureFromSurface(rend,tileSurf);
    SDL_FreeSurface(tileSurf);
    free(filepath);
}
void clearDataFromTile(LoadedTile* t) {
    for (int i=0; i<3; i++)
        *(t->tileData+i)='0';
    *(t->tileData+3)='\0';
}

void deleteLoadedTile(LoadedTile* t) {
    free(t->tileData);
    free(t->tileTexture);
}

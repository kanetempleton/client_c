#ifndef H_MAP
#define H_MAP
#define MAP_WIDTH 14
#define MAP_HEIGHT 12
#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define TILE_SIZE 32
#define TILE_DATA_SIZE 5
#define MAX_COORDINATE 9999
#define MIN_COORDINATE -9999
#include "SDL2/SDL.h"
#include "../entity/Player.h"
#include "LoadedTile.h"

typedef struct {
    char* mapstring;
    LoadedTile* tileCache[MAP_WIDTH*MAP_HEIGHT];
    SDL_Renderer* renderer;
    int* loadedTileCount;
    int* rendPlayers[MAP_WIDTH][MAP_HEIGHT];
    int* globalPlayerUpdateRequired;
    SDL_Texture* otherPlayer;
} Map;

int loadTile(Map* m, char* dataChunk);
Map * newMap();
void initMap(Map* m, SDL_Renderer* rend);
void renderMap(Map* m, Player* p);
int screenX(int x);
int screenY(int y);
void updateMapString(Map* m,char* changeTo);
void updateMapRight(Map* m, char* newData);
void updateMapLeft(Map* m, char* newData);
void updateMapUp(Map* m, char* newData);
void updateMapDown(Map* m, char* newData);
int computeMapDataSection(int x, int y);
void clearRenderMapData(Map* m);

void setTile(Map* m, int x, int y, char* t);

void getBase36(char* fill, int num);
#endif

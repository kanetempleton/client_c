#include "Player.h"
#include "../GameState.h"
Player* newPlayer() {
    return (Player*)malloc(sizeof(Player));
}

void initPlayer(Player* p, SDL_Renderer* r) {
    p->playerName = malloc(13);
    p->absX = malloc(sizeof(int));
    p->absY = malloc(sizeof(int));
    p->playerId = malloc(sizeof(int));
    p->mapSection = malloc(sizeof(int));
    p->playerRights = malloc(sizeof(int));
    *(p->playerId) = -1;
    *(p->absX) = -1;
    *(p->absY) = -1;
    *(p->mapSection) = -1;
    *(p->playerRights) = 0;
    p->gameRenderer = r;
    SDL_Surface* plrIconSurf= IMG_Load("data/assets/entity/player.png");
    p->plrImage = SDL_CreateTextureFromSurface(r,plrIconSurf);
    SDL_FreeSurface(plrIconSurf);
    p->guiSprites = newSpriteCache();
}

void deletePlayer(Player * p) {
    free(p->absX);
    free(p->absY);
    free(p->playerId);
    free(p->playerRights);
    free(p->mapSection);
    SDL_DestroyTexture(p->plrImage);
}

void renderPlayer(Player * p) {
    SDL_Rect plrRect = {192,160,TILE_WIDTH,TILE_HEIGHT};
    SDL_Rect plrRect2 = {TILE_SIZE*(*(p->absX)%MAP_WIDTH),TILE_SIZE*(*(p->absY)%MAP_HEIGHT),TILE_WIDTH,TILE_HEIGHT};
    //SDL_Rect plrRect = {*(p->absX),*(p->absY),TILE_WIDTH,TILE_HEIGHT};
    SDL_RenderCopy(p->gameRenderer,p->plrImage,NULL,&plrRect2);
}

void resetPlayer(Player* p) {
    *(p->playerId) = -1;
    *(p->absX) = -1;
    *(p->absY) = -1;
}

void setPlayerCoordinates(Player * p, int x, int y) {
    *(p->absX)=x;
    *(p->absY)=y;
}

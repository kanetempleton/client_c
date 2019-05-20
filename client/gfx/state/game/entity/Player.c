#include "Player.h"
#include "../GameState.h"
Player* newPlayer() {
    return (Player*)malloc(sizeof(Player));
}

void initPlayer(Player* p, SDL_Renderer* r,int x, int y) {
    p->absX = malloc(sizeof(int));
    p->absY = malloc(sizeof(int));
    *(p->absX) = x;
    *(p->absY) = y;
    p->gameRenderer = r;
    SDL_Surface* plrIconSurf= IMG_Load("gfx/assets/entity/player.png");
    p->plrImage = SDL_CreateTextureFromSurface(r,plrIconSurf);
    SDL_FreeSurface(plrIconSurf);
}

void deletePlayer(Player * p) {
    free(p->absX);
    free(p->absY);
    SDL_DestroyTexture(p->plrImage);
}

void renderPlayer(Player * p) {
    SDL_Rect plrRect = {*(p->absX),*(p->absY),TILE_WIDTH,TILE_HEIGHT};
    SDL_RenderCopy(p->gameRenderer,p->plrImage,NULL,&plrRect);
}

void setPlayerCoordinates(Player * p, int x, int y) {
    *(p->absX)=x;
    *(p->absY)=y;
}

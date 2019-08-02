#include "Entity.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include  "../map/Map.h"

Entity* newEntity() {
    return (Entity*)malloc(sizeof(Entity));
}
void initEntity(Entity* e, int id, int x, int y, SDL_Renderer* r) {
    e->id = malloc(sizeof(int));
    e->posX = malloc(sizeof(int));
    e->posY = malloc(sizeof(int));
    SDL_Surface* imgsurf = IMG_Load(getEntityImagePath(e));
    e->entityImage = SDL_CreateTextureFromSurface(r,imgsurf);
    SDL_FreeSurface(imgsurf);
    *(e->id) = id;
    *(e->posX) = x;
    *(e->posY) = y;
}
void setEntityCoordinates(Entity* e, int x, int y) {
    *(e->posX) = x;
    *(e->posY) = y;
}
void renderEntity(Entity* e, SDL_Renderer* rend) {
    SDL_Rect entityRect = {*(e->posX),*(e->posY),TILE_SIZE,TILE_SIZE};
    SDL_RenderCopy(rend,e->entityImage,NULL,&entityRect);
}

#ifndef H_ENTITY
#define H_ENTITY
#include "SDL2/SDL.h"
typedef struct {
    int* posX;
    int* posY;
    int* id;
    SDL_Texture* entityImage;
} Entity;
Entity* newEntity();
void initEntity(Entity* e, int id, int x, int y, SDL_Renderer* r);
void setEntityCoordinates(Entity* e, int x, int y);
void renderEntity(Entity* e, SDL_Renderer* rend);
char* getEntityImagePath(Entity* e) {
    switch (*(e->id)) {
        case 0:
            return "data/assets/entity/player.png";
    }
    return "data/assets/entity/player.png";
}

#endif

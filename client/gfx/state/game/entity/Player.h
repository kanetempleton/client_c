#ifndef H_PLAYER
#define H_PLAYER
#include "SDL2/SDL.h"
typedef struct {
    int * absX;
    int * absY;
    SDL_Texture* plrImage;
    SDL_Renderer* gameRenderer;
    char * userName;
} Player;
Player * newPlayer();
void initPlayer(Player* p, SDL_Renderer* r, int x, int y);
void deletePlayer(Player* p);
void renderPlayer(Player* p);
void setPlayerCoordinates(Player * p, int x, int y);
#endif

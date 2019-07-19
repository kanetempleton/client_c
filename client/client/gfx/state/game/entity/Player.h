#ifndef H_PLAYER
#define H_PLAYER
#include "SDL2/SDL.h"
#include "../../../SpriteCache.h"
typedef struct {
    int * absX;
    int * absY;
    int * mapSection;
    SDL_Renderer* gameRenderer;
    SDL_Texture* plrImage;
    char * playerName;
    int * playerId;
    int * playerRights;
    SpriteCache* guiSprites;
} Player;
Player * newPlayer();
void initPlayer(Player* p, SDL_Renderer* r);
void resetPlayer(Player* p);
void deletePlayer(Player* p);
void renderPlayer(Player* p);
void setPlayerCoordinates(Player * p, int x, int y);
#endif

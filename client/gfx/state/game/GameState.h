#ifndef H_GAMESTATE
#define H_GAMESTATE
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "entity/Player.h"
#define TILE_WIDTH 32
#define TILE_HEIGHT 32
typedef struct {
    SDL_Renderer* stateRenderer;
    SDL_Texture* gameFrameTexture;
    Player* you;
} GameState;
GameState* newGameState();
void initGameState(GameState* s, SDL_Renderer* r);
void updateCoordinates(GameState* s, int x, int y);
void deleteGameState(GameState*s);
void renderGameState(GameState* s);
void processKeys_Game(GameState* s, int key);
#endif

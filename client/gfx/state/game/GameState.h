#ifndef H_GAMESTATE
#define H_GAMESTATE
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "entity/Player.h"
#include "../../component/button.h"
#include "map/Map.h"
#define NUM_GAME_BUTTONS 1
typedef struct {
    SDL_Renderer* stateRenderer;
    SDL_Texture* gameFrameTexture;
    Button* buttons[NUM_GAME_BUTTONS];
    Map * gameMap;
} GameState;
GameState* newGameState();
void initGameState(GameState* s, SDL_Renderer* r);
void updateCoordinates(GameState* s, int x, int y);
void deleteGameState(GameState*s);
void renderGameState(GameState* s);
void processKeys_Game(GameState* s, int key);
void processClicks_Game(GameState* s, int x, int y);
#endif

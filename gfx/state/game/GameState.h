#ifndef H_GAMESTATE
#define H_GAMESTATE
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "entity/Player.h"
#include "../../component/button.h"
#include "map/Map.h"
#include "hud/HUD.h"
#include "cpanel/CPanel.h"
#include "infobox/InfoBox.h"

#define NUM_GAME_BUTTONS 1
typedef struct {
    SDL_Renderer* stateRenderer;
    SDL_Texture* gameFrameTexture;
    Button* buttons[NUM_GAME_BUTTONS];
    Map * gameMap;
    GameHUD* gameHUD;
    int* cursorX;
    int* cursorY;
} GameState;
ControlPanel* gameCPanel;
GameState* newGameState();
void initGameState(GameState* s, SDL_Renderer* r);
void updateCoordinates(GameState* s, int x, int y);
void deleteGameState(GameState*s);
void renderGameState(GameState* s);
void processKeys_Game(GameState* s, int key);
void processClicks_Game(GameState* s, int x, int y);
void processMouseMotion_Game(GameState* s, int x, int y);
void setCursor(int id);
#endif

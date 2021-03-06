#ifndef H_GUI
#define H_GUI
#include "state/login/LoginState.h"
#include "state/game/GameState.h"
#include "state/game/entity/Player.h"
#include "SpriteCache.h"
#include <pthread.h>

#define GUI_WINDOW_WIDTH 640
#define GUI_WINDOW_HEIGHT 576

pthread_mutex_t guiLock;

typedef struct {
    int* mapEditMode;
    int* cursorID;
    int* mapSend;
    char* tempMapString;
    int* holdingMouse;
} GUISettings;

typedef struct {
    char * updateString;
    LoginState* loginState;
    GameState* gameState;
    int * currentState;
} GUI;

Player * yourPlayer;
GUISettings* yourSettings;
SDL_Renderer* Main_Renderer;
SpriteCache* spriteCache;
GUI * newGUI();
void initGUI(GUI * me);
void deleteGUI(GUI * me);
//void * startGUI(void * arg); //enable multithreading  NEVERMIND
void shout();
void loadGUIWindow(GUI * me);
void quitGUI();
#endif

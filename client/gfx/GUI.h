#ifndef H_GUI
#define H_GUI
#include "state/login/LoginState.h"
#include "state/game/GameState.h"
#include "state/game/entity/Player.h"

#define GUI_WINDOW_WIDTH 640
#define GUI_WINDOW_HEIGHT 576

typedef struct {
    int* mapEditMode;
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
GUI * newGUI();
void initGUI(GUI * me);
void deleteGUI(GUI * me);
//void * startGUI(void * arg); //enable multithreading  NEVERMIND
void shout();
void loadGUIWindow(GUI * me);
void quitGUI();
#endif

#ifndef H_GUI
#define H_GUI
#include "state/login/LoginState.h"
#include "state/game/GameState.h"
#include "state/game/entity/Player.h"
typedef struct {
    char * updateString;
    LoginState* loginState;
    GameState* gameState;
    int * currentState;
} GUI;
Player * yourPlayer;
GUI * newGUI();
void initGUI(GUI * me);
void deleteGUI(GUI * me);
//void * startGUI(void * arg); //enable multithreading  NEVERMIND
void shout();
void loadGUIWindow(GUI * me);
void quitGUI();
#endif

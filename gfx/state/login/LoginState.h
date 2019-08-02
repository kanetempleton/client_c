#ifndef H_LOGINSTATE
#define H_LOGINSTATE
#include "../../text/KeyboardHandler.h"
#include "../../text/KeyboardConstants.h"
#include "SDL2/SDL.h"
#include "../../component/button.h"
#define NUM_LOGIN_BUTTONS 2
typedef struct {
    TextInput* usernameText;
    TextInput* passwordText;
    SDL_Texture* usernameTexture;
    SDL_Texture* passwordTexture;
    int * userWidth;
    int * userHeight;
    int * passWidth;
    int * passHeight;
    int * activeField;
    Button* buttons[NUM_LOGIN_BUTTONS];
    SDL_Renderer* stateRenderer;
    int * substate;
    char * infoText;
} LoginState;
LoginState* newLoginState();
void initLoginState(LoginState* state, SDL_Renderer* renderer);
void deleteLoginState(LoginState* state);
void renderLoginState(LoginState* state, TTF_Font* font, SDL_Color color, int textUpdateRequired);
int processKeys_Login(LoginState* state, int keysym);
void processClicks_Login(LoginState* state, int clickX, int clickY);
void enterLoginSubstate(LoginState* state, int sub);
#endif

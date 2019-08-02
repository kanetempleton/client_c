#ifndef H_CPANEL
#define H_CPANEL
#include "SDL2/SDL.h"
#include "../../../component/button.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "../../../text/KeyboardHandler.h"

//graphics constants
#define CPANEL_START_X 448
#define CPANEL_START_Y 384
#define CPANEL_WIDTH 192
#define CPANEL_HEIGHT 192

//data field constants
#define CPANEL_NUM_TEXT_FIELDS 10
#define CPANEL_NUM_BUTTONS 4
#define CPANEL_BUTTON_INDEX 60

//button stuff
#define CPANEL_BUTTON0_X 478
#define CPANEL_BUTTON0_Y 424

//states
#define CPANEL_STATE_MAPEDIT 1

typedef struct {
    int* currentState;
    SDL_Texture* background;
    SDL_Texture* text[CPANEL_NUM_TEXT_FIELDS];
    Button* buttons[CPANEL_NUM_BUTTONS];
    TTF_Font* font;
    TextInput* consoleInput;
    int* consoleInputEnabled;
} ControlPanel;

ControlPanel* newControlPanel();
void initControlPanel(ControlPanel* pan, SDL_Renderer* r);
void deleteControlPanel(ControlPanel* pan);
void renderControlPanel(ControlPanel* pan, SDL_Renderer* r);
void setControlPanelState(ControlPanel* pan, int state);
void processClicks_CPanel(ControlPanel* pan, int clickX, int clickY);
void processKeys_CPanel(ControlPanel* pan, int keyid);

void toggleConsoleInput(ControlPanel* pan);

void cpanel_clickButton1(ControlPanel* pan);
void cpanel_clickButton2(ControlPanel* pan);
void cpanel_clickButton3(ControlPanel* pan);

void resetControlPanelState(ControlPanel* pan);
#endif

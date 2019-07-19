#include "CPanel.h"
#include <stdlib.h>
#include "SDL2/SDL_image.h"
#include "cstate/MapEditor.h"
#include "../../../GUI.h"

ControlPanel* newControlPanel() {
    return (ControlPanel*)malloc(sizeof(ControlPanel));
}
void initControlPanel(ControlPanel* pan, SDL_Renderer* r) {
    pan->currentState = malloc(sizeof(int));
    *(pan->currentState) = 0;
    SDL_Surface* bgSurf = IMG_Load("data/assets/interface/cpanel/cpanel.png");
    pan->background = SDL_CreateTextureFromSurface(r,bgSurf);
    SDL_FreeSurface(bgSurf);

    for (int i=0; i<CPANEL_NUM_BUTTONS; i++) {
        int id = CPANEL_BUTTON_INDEX;
        pan->buttons[i]=newButton();
        initButton(pan->buttons[i],id,CPANEL_BUTTON0_X,CPANEL_BUTTON0_Y+42*i);
        loadButtonImage(pan->buttons[i],Main_Renderer);
    }

    TTF_Font* fawnt = TTF_OpenFont("data/assets/fonts/Arial.ttf",12);
    pan->font = fawnt;

    pan->consoleInput = newTextInputField();
    initTextInputField(pan->consoleInput, 3);

    pan->consoleInputEnabled = malloc(sizeof(int));
    *(pan->consoleInputEnabled) = 0;
    //pan->renderer=r;

}
void resetControlPanelState(ControlPanel* pan) {
    *(pan->currentState)=0;
    *(pan->consoleInputEnabled) = 0;
    clearTextField(pan->consoleInput);
    //*(pan->consoleInputEnabled) = 0;
}
void deleteControlPanel(ControlPanel* pan) {
    free(pan->currentState);
    SDL_DestroyTexture(pan->background);
    SDL_DestroyTexture(pan->text[0]); //make this legit
}
void renderControlPanel(ControlPanel* pan, SDL_Renderer* r) {
    SDL_Rect bgRect = {CPANEL_START_X,CPANEL_START_Y,CPANEL_WIDTH,CPANEL_HEIGHT};
    SDL_RenderCopy(r,pan->background,NULL,&bgRect);
    switch (*(pan->currentState)) {
        case CPANEL_STATE_MAPEDIT:
            renderMapEditor(pan,pan->font,r);
            break;
        default:
            break;
    }
}

void setControlPanelState(ControlPanel* pan, int state) {
    *(pan->currentState)=state;
    SDL_Surface* txt0;
    SDL_Color white = {255,255,255};

    switch (state) {
        case CPANEL_STATE_MAPEDIT:
            txt0 = TTF_RenderText_Solid(pan->font,"Enter Tile Data",white);
            //TTF_SizeText(fawnt,"Enter Tile Data",NULL,NULL);
            pan->text[0] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            SDL_FreeSurface(txt0);
            txt0 = TTF_RenderText_Solid(pan->font,"Send Map to Server",white);
            pan->text[1] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            SDL_FreeSurface(txt0);
            txt0 = TTF_RenderText_Solid(pan->font,"Clear",white);
            pan->text[2] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            SDL_FreeSurface(txt0);
            break;
        default:
            printf("[Control Panel] unsupported state\n");
            break;
    }
}


void processClicks_CPanel(ControlPanel* pan, int clickX, int clickY) {
    for (int i=0; i<CPANEL_NUM_BUTTONS; i++) {
        int id = CPANEL_BUTTON_INDEX;
        if (clickButton(pan->buttons[i],clickX,clickY)) {
            switch (i) {
                case 0:
                    cpanel_clickButton1(pan);
                    break;
                case 1:
                    cpanel_clickButton2(pan);
                    break;
                case 2:
                    cpanel_clickButton3(pan);
                    break;
            }
        }
    }
}

void processKeys_CPanel(ControlPanel* pan, int keyid) {
    if (*(pan->consoleInputEnabled))
        addKey(pan->consoleInput,keyid);
}

void toggleConsoleInput(ControlPanel* pan) {
    if (*(pan->consoleInputEnabled)) {
        *(pan->consoleInputEnabled) = 0;
    }
    else
        *(pan->consoleInputEnabled) = 1;
}

void cpanel_clickButton1(ControlPanel* pan) {
    switch (*(pan->currentState)) {
        case CPANEL_STATE_MAPEDIT:
            processCpanelClick_MapEditor(pan,1);
            break;
    }
}

void cpanel_clickButton2(ControlPanel* pan) {
    switch (*(pan->currentState)) {
        case CPANEL_STATE_MAPEDIT:
            processCpanelClick_MapEditor(pan,2);
            break;
    }
}

void cpanel_clickButton3(ControlPanel* pan) {
    switch (*(pan->currentState)) {
        case CPANEL_STATE_MAPEDIT:
            processCpanelClick_MapEditor(pan,3);
            break;
    }
}

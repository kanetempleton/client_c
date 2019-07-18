#include "CPanel.h"
#include <stdlib.h>
#include "SDL2/SDL_image.h"
#include "cstate/MapEditor.h"
#include "SDL2_ttf/SDL_ttf.h"
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
        initButton(pan->buttons[i],id+i,CPANEL_BUTTON0_X,CPANEL_BUTTON0_Y);
        loadButtonImage(pan->buttons[i],Main_Renderer);
    }

    //pan->renderer=r;

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
            renderMapEditor(pan,r);
            break;
        default:
            break;
    }
}

void setControlPanelState(ControlPanel* pan, int state) {
    *(pan->currentState)=state;
    SDL_Surface* txt0;
    SDL_Color white = {255,255,255};
    TTF_Font* fawnt = TTF_OpenFont("data/assets/fonts/Arial.ttf",16);
    switch (state) {
        case CPANEL_STATE_MAPEDIT:
            printf("about to set sttae\n");
            txt0 = TTF_RenderText_Solid(fawnt,"Enter Tile Data",white);
            printf("about to set sttae2\n");
            pan->text[0] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            printf("about to set sttae4\n");
            SDL_FreeSurface(txt0);
            printf(" to set stta5e\n");
            break;
        default:
            printf("[Control Panel] unsupported state\n");
            break;
    }
}


void processClicks_CPanel(ControlPanel* pan, int clickX, int clickY) {
    switch (*(pan->currentState)) {
        case CPANEL_STATE_MAPEDIT:
            break;
    }
}

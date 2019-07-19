#include "MapEditor.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "../../../../GUI.h"
#include "../../../../../net/communication/SendMessage.h"

void renderMapEditor(ControlPanel* pan, TTF_Font* font, SDL_Renderer* r) {
    SDL_Rect buttonRect = {478,424,128,32};
    SDL_Rect txtRect = {492,434,128,12};
    SDL_Rect txtRect2 = {520,460,128,12};
    SDL_Color White = {255,255,255};
    //SDL_RenderCopy(r,pan->longButtonTexture,NULL,&buttonRect);
    if (*(pan->consoleInputEnabled)) {
        TTF_SizeText(font,"Done",&txtRect.w,&txtRect.h);
    } else {
        TTF_SizeText(font,"Enter Tile Data",&txtRect.w,&txtRect.h);
    }


    for (int i=0; i<MAPEDITOR_NUM_BUTTONS; i++) {
        SDL_Rect txtRect3 = {492,434+42*i,128,12};
        renderButton(pan->buttons[i],r);
        if (pan->text[i]!=NULL) {
            //TTF_SizeText(font,pan->text[i]->build,&txtRect3.w,&txtRect3.h);
            if (i==1)
                TTF_SizeText(font,"Send Map to Server",&txtRect3.w,&txtRect3.h);
            else if (i==2)
                TTF_SizeText(font,"Done",&txtRect3.w,&txtRect3.h);
            else if (i==0)
                TTF_SizeText(font,"Enter Tile Data",&txtRect3.w,&txtRect3.h);

            SDL_RenderCopy(r,pan->text[i],NULL,&txtRect3);
        }
    }

    TTF_SizeText(font,pan->consoleInput->build,&txtRect2.w,&txtRect2.h);
    SDL_Surface* infoSurface = TTF_RenderText_Solid(font,pan->consoleInput->build,White);
    SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(r,infoSurface);
    SDL_FreeSurface(infoSurface);
    SDL_RenderCopy(r,infoTexture,NULL,&txtRect2);
    SDL_DestroyTexture(infoTexture);
}


void displayInputTileField(ControlPanel* pan) {

}


void processCpanelClick_MapEditor(ControlPanel* pan, int button) {
    SDL_Surface* txt0;
    SDL_Color white = {255,255,255};
    /*if (!(*(yourSettings->mapEditMode))) {
        resetControlPanelState(pan);
    }*/
    if (button==1) {
        toggleConsoleInput(pan);
        if (*(pan->consoleInputEnabled)) {
            txt0 = TTF_RenderText_Solid(pan->font,"Lookup",white);
            pan->text[0] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            SDL_FreeSurface(txt0);
        } else {
            if (strlen(pan->consoleInput->build)==3) {
                searchTile(pan);
            }
            txt0 = TTF_RenderText_Solid(pan->font,"Enter Tile Data",white);
            pan->text[0] = SDL_CreateTextureFromSurface(Main_Renderer,txt0);
            SDL_FreeSurface(txt0);

        }
    } else if (button==2) {
        //*(yourSettings->mapSend)=1;
        if (*(yourSettings->mapEditMode)) {
            if (!(*(yourSettings->mapSend))) {
                printf("you must add map data first\n");
            } else {
                submitMapEdit(yourSettings->tempMapString);
                *(yourSettings->cursorID)=-1;
                *(yourSettings->mapEditMode)=0;
                *(yourSettings->mapSend)=0;
                resetControlPanelState(pan);
            }
        }
    }
}


void searchTile(ControlPanel* pan) {
    int tile = strtol(pan->consoleInput->build,NULL,36);
    setCursor(tile);
    //*(yourSettings->cursorID)=tile;
}

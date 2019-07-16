#include "GameState.h"
#include "entity/Player.h"
#include "../../../net/communication/Codes.h"
#include "../../GUI.h"

GameState* newGameState() {
    return (GameState*) malloc(sizeof(GameState));
}

void initGameState(GameState* gs, SDL_Renderer* rend) {
    gs->stateRenderer = rend;
    SDL_Surface* gameFrameSurf = IMG_Load("data/assets/gameframe.png");
    gs->gameFrameTexture = SDL_CreateTextureFromSurface(gs->stateRenderer,gameFrameSurf);
    SDL_FreeSurface(gameFrameSurf);
    gs->buttons[0] = newButton();
    initButton(gs->buttons[0],2,575,5);
    gs->gameMap = newMap();
    initMap(gs->gameMap,rend);
    //sendPlayerInfoRequest();
}

void deleteGameState(GameState* gs) {
    SDL_DestroyTexture(gs->gameFrameTexture);
}

void renderGameState(GameState* gs) {
    //SDL_Surface* Loading_Surf = IMG_Load("gfx/assets/background.png"); //TODO: init the background in init method so we dont have to do it over and over again
    //SDL_Texture* Background_Tx = SDL_CreateTextureFromSurface(state->stateRenderer, Loading_Surf);
    //SDL_FreeSurface(Loading_Surf);
    if (gs==NULL)
        return;
    if (gs->stateRenderer==NULL || gs->gameFrameTexture==NULL)
        return;
    SDL_RenderCopy(gs->stateRenderer,gs->gameFrameTexture,NULL,NULL);
    renderButton(gs->buttons[0],gs->stateRenderer);
    //SDL_DestroyTexture(Background_Tx);
    renderMap(gs->gameMap,yourPlayer);
    //renderPlayer(yourPlayer);
}

void processKeys_Game(GameState* gs, int keysym) {
    switch (keysym) {
        case SDLK_DOWN:
            //setPlayerCoordinates(yourPlayer,*(yourPlayer->absX),*(yourPlayer->absY)+1);
            sendUpdatePlayerCoordinatesRequest(*(yourPlayer->absX),*(yourPlayer->absY)+1);
            //printf("walk down\n");
            break;
        case SDLK_UP:
            //setPlayerCoordinates(yourPlayer,*(yourPlayer->absX),*(yourPlayer->absY)-1);
            sendUpdatePlayerCoordinatesRequest(*(yourPlayer->absX),*(yourPlayer->absY)-1);
            //printf("you abs = %d,%d\n",*(yourPlayer->absX),*(yourPlayer->absY));
            break;
        case SDLK_LEFT:
            //setPlayerCoordinates(yourPlayer,*(yourPlayer->absX)-1,*(yourPlayer->absY));
            sendUpdatePlayerCoordinatesRequest(*(yourPlayer->absX)-1,*(yourPlayer->absY));
            break;
        case SDLK_RIGHT:
            //setPlayerCoordinates(yourPlayer,*(yourPlayer->absX)+1,*(yourPlayer->absY));
            sendUpdatePlayerCoordinatesRequest(*(yourPlayer->absX)+1,*(yourPlayer->absY));
            break;
    }
    /*if (*(state->activeField)==0) {
        if (addKey(state->usernameText,keysym) == 2) {
            *(state->activeField)=1;
            return 0;
        }
        return 1;
    }
    else if (*(state->activeField)==1) {
        if (addKey(state->passwordText,keysym) == 2) {
            *(state->activeField)=0;
            return 0;
        }
        return 1;
    }
    return 0;*/
}

void processClicks_Game(GameState* gs, int clickX, int clickY) {
    for (int i=0; i<NUM_GAME_BUTTONS; i++) {
        int lowx = *(gs->buttons[i]->absX);
        int highx = lowx+*(gs->buttons[i])->width;
        int lowy = *(gs->buttons[i]->absY);
        int highy = lowy+*(gs->buttons[i])->height;
        if (clickX >= lowx && clickX <= highx && clickY >= lowy && clickY <= highy) {
            //clickButton(state->buttons[i]); //maybe unnecessary
            if (!*(gs->buttons[i]->isVisible))
                return;
            switch (i) {
                case 0: // "logout" button
                    printf("logmeout]\n");
                    sendLogoutRequest();
                    break;

            }
        }
    }
}

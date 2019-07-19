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
    //gs->buttons[0] = newButton();
    //initButton(gs->buttons[0],2,575,5);
    gs->gameMap = newMap();
    initMap(gs->gameMap,rend);
    gs->gameHUD = newHUD();
    initHUD(gs->gameHUD,rend);

    gs->cursorX = malloc(sizeof(int));
    gs->cursorY = malloc(sizeof(int));
    *(gs->cursorX) = 0;
    *(gs->cursorY) = 0;

    gameCPanel = newControlPanel();
    initControlPanel(gameCPanel,rend);
    //sendPlayerInfoRequest();
}

void deleteGameState(GameState* gs) {
    SDL_DestroyTexture(gs->gameFrameTexture);
}

void renderGameState(GameState* gs) {
    if (gs==NULL)
        return;
    if (gs->stateRenderer==NULL || gs->gameFrameTexture==NULL)
        return;
    SDL_RenderCopy(gs->stateRenderer,gs->gameFrameTexture,NULL,NULL);
    renderMap(gs->gameMap,yourPlayer);
    renderHUD(gs->gameHUD,gs->stateRenderer);
    renderControlPanel(gameCPanel,gs->stateRenderer);

    SDL_Rect cursorRect = {*(gs->cursorX)-(TILE_SIZE/2),*(gs->cursorY)-(TILE_SIZE/2),TILE_SIZE,TILE_SIZE};
    if (*(yourSettings->cursorID) >=0) {
        SDL_RenderCopy(gs->stateRenderer,yourPlayer->guiSprites->gameCursor,NULL,&cursorRect);
    }
    //renderButton(gs->buttons[0],gs->stateRenderer);
}

void processKeys_Game(GameState* gs, int keysym) {
    processKeys_CPanel(gameCPanel,keysym);
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

    processClicks_HUD(gs->gameHUD,clickX,clickY);
    processClicks_CPanel(gameCPanel,clickX,clickY);
    if (clickX<(TILE_SIZE*MAP_WIDTH) && clickY<(TILE_SIZE*MAP_HEIGHT)) {
        if (*(yourSettings->cursorID) > -1) {
            int scrX = clickX/TILE_SIZE;
            int scrY = clickY/TILE_SIZE;
            setTile(gs->gameMap,scrX,scrY,gameCPanel->consoleInput->build);
            *(yourSettings->mapSend)=1;
        }
    }
    /*for (int i=0; i<NUM_GAME_BUTTONS; i++) {
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
    }*/
}

void processMouseMotion_Game(GameState* gs, int x, int y) {
    SDL_Rect cursorRect = {x,y,32,32};
    if (*(yourSettings->cursorID) >=0) {
        if (yourPlayer->guiSprites->gameCursor!=NULL) {
            *(gs->cursorX) = x;
            *(gs->cursorY) = y;
            if (*(yourSettings->holdingMouse)) {
                int scrX = x/TILE_SIZE;
                int scrY = y/TILE_SIZE;
                printf("setting tile at %d %d\n",scrX,scrY);
                setTile(gs->gameMap,scrX,scrY,gameCPanel->consoleInput->build);
            }
            //SDL_RenderCopy(gs->stateRenderer,yourPlayer->guiSprites->gameCursor,NULL,&cursorRect);
        }
    }
}

void setCursor(int id) {
    printf("setting the cursor\n");

    char buf[6];
    sprintf(buf,"%d",id);
    char* filepath = malloc(strlen("data/assets/map/.png")+TILE_DATA_SIZE+strlen(buf)+8);
    strcpy(filepath,"data/assets/map/");
    strcat(filepath,buf);
    strcat(filepath,".png");

    SDL_Surface* cursorSurface = IMG_Load(filepath);
    yourPlayer->guiSprites->gameCursor = SDL_CreateTextureFromSurface(yourPlayer->guiSprites->spriteRenderer,cursorSurface);
    SDL_FreeSurface(cursorSurface);
    *(yourSettings->cursorID) = id;

    free(filepath);
}

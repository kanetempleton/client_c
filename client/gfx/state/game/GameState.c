#include "GameState.h"
#include "entity/Player.h"

GameState* newGameState() {
    return (GameState*) malloc(sizeof(GameState));
}

void initGameState(GameState* gs, SDL_Renderer* rend) {
    gs->stateRenderer = rend;
    SDL_Surface* gameFrameSurf = IMG_Load("gfx/assets/gameframe.png");
    gs->gameFrameTexture = SDL_CreateTextureFromSurface(gs->stateRenderer,gameFrameSurf);
    SDL_FreeSurface(gameFrameSurf);
    gs->you = newPlayer();
    initPlayer(gs->you,rend,50,50);
}

void deleteGameState(GameState* gs) {
    SDL_DestroyTexture(gs->gameFrameTexture);
}

void renderGameState(GameState* gs) {
    //SDL_Surface* Loading_Surf = IMG_Load("gfx/assets/background.png"); //TODO: init the background in init method so we dont have to do it over and over again
    //SDL_Texture* Background_Tx = SDL_CreateTextureFromSurface(state->stateRenderer, Loading_Surf);
    //SDL_FreeSurface(Loading_Surf);
    SDL_RenderCopy(gs->stateRenderer,gs->gameFrameTexture,NULL,NULL);
    //SDL_DestroyTexture(Background_Tx);
    renderPlayer(gs->you);
}

void processKeys_Game(GameState* gs, int keysym) {
    switch (keysym) {
        case SDLK_DOWN:
            setPlayerCoordinates(gs->you,*(gs->you->absX),*(gs->you->absY)+1);
            printf("walk down\n");
            break;
        case SDLK_UP:
            setPlayerCoordinates(gs->you,*(gs->you->absX),*(gs->you->absY)-1);
            break;
        case SDLK_LEFT:
            setPlayerCoordinates(gs->you,*(gs->you->absX)-1,*(gs->you->absY));
            break;
        case SDLK_RIGHT:
            setPlayerCoordinates(gs->you,*(gs->you->absX)+1,*(gs->you->absY));
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

#include <stdlib.h>
#include "LoginState.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "../text/KeyboardHandler.h"
#include "../text/KeyboardConstants.h"
#include "../component/button.h"
#include "../GUI.h"
#include "../../net/client.h"
#include "../../net/communication/Codes.h"
#include <string.h>

LoginState* newLoginState() {
    return (LoginState*) malloc(sizeof(LoginState));
}

void initLoginState(LoginState* state, SDL_Renderer* renderer, TTF_Font* font) {
    state->usernameText = newTextInputField();
    state->passwordText = newTextInputField();
    state->activeField = malloc(sizeof(int));
    initTextInputField(state->usernameText,12);
    initTextInputField(state->passwordText,20);
    *(state->activeField) = 0;

    state->userWidth = malloc(sizeof(int));
    state->userHeight = malloc(sizeof(int));
    state->passWidth = malloc(sizeof(int));
    state->passHeight = malloc(sizeof(int));
    *(state->userWidth) = 12;
    *(state->userHeight) = 16;
    *(state->passWidth) = 12;
    *(state->passHeight) = 16;

    state->infoText = "Please enter your username and password.";

    state->stateRenderer = renderer;
    state->substate = malloc(sizeof(int));
    *state->substate = 0;

    SDL_Color White = {255,255,255};
    SDL_Surface* usernameSurface = TTF_RenderText_Solid(font,state->usernameText->build,White);
    state->usernameTexture = SDL_CreateTextureFromSurface(state->stateRenderer,usernameSurface);
    SDL_FreeSurface(usernameSurface);

    SDL_Surface* passwordSurface = TTF_RenderText_Solid(font,state->passwordText->build,White);
    state->passwordTexture = SDL_CreateTextureFromSurface(state->stateRenderer,passwordSurface);
    SDL_FreeSurface(passwordSurface);

    state->buttons[0] = newButton();
    state->buttons[1] = newButton();
    initButton(state->buttons[0],0,375,375);
    initButton(state->buttons[1],1,200,375);

}

void deleteLoginState(LoginState* state) {
    deleteTextInputField(state->usernameText);
    deleteTextInputField(state->passwordText);
    SDL_DestroyTexture(state->usernameTexture);
    SDL_DestroyTexture(state->passwordTexture);
    //free(state->usernameText);
    //free(state->passwordText);
    free(state->activeField);
    free(state->userWidth);
    free(state->userHeight);
    free(state->passWidth);
    free(state->passHeight);
    deleteButton(state->buttons[0]);
    deleteButton(state->buttons[1]);
    //free(state->buttons[0]);
    //free(state->buttons[1]);
    //free(state->infoText);
    //free(state->usernameRect);
    //free(state->passwordRect);
    //free(state);
}

void renderLoginState(LoginState* state, TTF_Font* font, SDL_Color color, int textUpdateRequired) {
    //render login text
    SDL_Color White = {255,255,255};
    SDL_Color Cyan = {0,255,255};
    //TTF_Font* Arial = TTF_OpenFont("gfx/assets/fonts/Arial.ttf",16);
    SDL_Rect usernameRect = {190,250,*(state->userWidth),*(state->userHeight)};
    SDL_Rect passwordRect = {190,325,*(state->passWidth),*(state->passHeight)};
    SDL_Rect infoRect0 = {180,220,100,50};
    SDL_Rect infoRect = {250,220,100,50};

    SDL_Surface* Loading_Surf = IMG_Load("gfx/assets/background.png"); //TODO: init the background in init method so we dont have to do it over and over again
    SDL_Texture* Background_Tx = SDL_CreateTextureFromSurface(state->stateRenderer, Loading_Surf);
    SDL_FreeSurface(Loading_Surf);
    SDL_RenderCopy(state->stateRenderer,Background_Tx,NULL,NULL);
    SDL_DestroyTexture(Background_Tx);
    //SDL_Surface* loginTextSurface = TTF_RenderText_Solid(Arial,state->usernameText->build,White);
    if (strlen(state->infoText)>=40) {
        TTF_SizeText(font,state->infoText,&infoRect0.w,&infoRect0.h);
        SDL_Surface* infoSurface = TTF_RenderText_Solid(font,state->infoText,Cyan);
        SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(state->stateRenderer,infoSurface);
        SDL_FreeSurface(infoSurface);
        SDL_RenderCopy(state->stateRenderer,infoTexture,NULL,&infoRect0);
        SDL_DestroyTexture(infoTexture);
    }
    else if (strlen(state->infoText)>0) {
        TTF_SizeText(font,state->infoText,&infoRect.w,&infoRect.h);
        SDL_Surface* infoSurface = TTF_RenderText_Solid(font,state->infoText,Cyan);
        SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(state->stateRenderer,infoSurface);
        SDL_FreeSurface(infoSurface);
        SDL_RenderCopy(state->stateRenderer,infoTexture,NULL,&infoRect);
        SDL_DestroyTexture(infoTexture);
    }
    if (textUpdateRequired == 1) {
        SDL_Surface* userSurface = TTF_RenderText_Solid(font,state->usernameText->build,White);
        state->usernameTexture = SDL_CreateTextureFromSurface(state->stateRenderer,userSurface);
        TTF_SizeText(font,state->usernameText->build,(state->userWidth),(state->userHeight));
        SDL_FreeSurface(userSurface);

        char * pwdHidden = malloc(sizeof(char)*strlen(state->passwordText->build));
        strcpy(pwdHidden,"*");
        for (int i=1; i<strlen(state->passwordText->build); i++)
            strcat(pwdHidden,"*");
        SDL_Surface* passwordSurface = TTF_RenderText_Solid(font,pwdHidden,White);
        state->passwordTexture = SDL_CreateTextureFromSurface(state->stateRenderer,passwordSurface);
        TTF_SizeText(font,state->passwordText->build,state->passWidth,state->passHeight);
        SDL_FreeSurface(passwordSurface);
        //textUpdateRequired=0;
    }
    renderButton(state->buttons[0],state->stateRenderer);
    renderButton(state->buttons[1],state->stateRenderer);

    SDL_RenderCopy(state->stateRenderer, state->usernameTexture, NULL, &usernameRect);
    SDL_RenderCopy(state->stateRenderer, state->passwordTexture, NULL, &passwordRect);
    //TTF_CloseFont(Arial);
}

int processKeys_Login(LoginState* state, int keysym) {
    if (*(state->activeField)==0) {
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
    return 0;
}

void enterLoginSubstate(LoginState* state, int go2) {
    *(state->substate) = go2;
    switch (go2) {
        case 0: //return from login request ; invalid or error connecting
            *(state->buttons[0]->isVisible)=1;
            *(state->buttons[1]->isVisible)=1;
            printf("enter main state\n");
            state->infoText = "Invalid password.";
            break;
        case 1: //waiting for login request to be answered
            state->infoText = "Sending login request...";
            *(state->buttons[0]->isVisible)=0;
            *(state->buttons[1]->isVisible)=0;
            //state->infoText = "";
            printf("waiting for login request to be answered\n");
            break;
    }
}

void processClicks_Login(LoginState* state, int clickX, int clickY) {
    for (int i=0; i<NUM_LOGIN_BUTTONS; i++) {
        int lowx = *(state->buttons[i]->absX);
        int highx = lowx+*(state->buttons[i])->width;
        int lowy = *(state->buttons[i]->absY);
        int highy = lowy+*(state->buttons[i])->height;
        if (clickX >= lowx && clickX <= highx && clickY >= lowy && clickY <= highy) {
            //clickButton(state->buttons[i]); //maybe unnecessary
            if (!*(state->buttons[i]->isVisible))
                return;
            switch (i) {
                case 0: // click "enter" button
                    if ((strlen(state->usernameText->build)>0) && (strlen(state->passwordText->build)>0)) {
                        sendLoginRequest(state->usernameText->build,state->passwordText->build);
                        enterLoginSubstate(state,1);
                    }
                    break;
                case 1: //click "exit" button
                    quitGUI();
                    shutDownClient();
                    break;
            }
        }
    }
}

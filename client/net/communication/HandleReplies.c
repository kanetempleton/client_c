#include "HandleReplies.h"
#include "Codes.h"
#include <string.h>

ReplyHandler* newReplyHandler() {
    return (ReplyHandler*)malloc(sizeof(ReplyHandler));
}

void initReplyHandler(ReplyHandler* rh, GUI* g) {
    rh->gui = g;
}

void deleteReplyHandler(ReplyHandler* rh) {
    deleteGUI(rh->gui);
    free(rh);
}

void handleReply(ReplyHandler* rh, char* repl) {
    if (strcmp(repl,"successlogin")==0) {
        //enter the game
        initGameState(rh->gui->gameState,rh->gui->loginState->stateRenderer);
        deleteLoginState(rh->gui->loginState);
        *(rh->gui->currentState) = 1;
        printf("enter the game!!!!!\n");
        //sendPlayerInfoRequest();
    }
    else if (strcmp(repl,"createnewprofile")==0) {
        //enter the game
        printf("MAKE A NEW PROFILE!!!!!\n");
        initGameState(rh->gui->gameState,rh->gui->loginState->stateRenderer);
        deleteLoginState(rh->gui->loginState);
        *(rh->gui->currentState) = 1;
        //sendPlayerInfoRequest();
    }
    else if (strcmp(repl,"invalidlogin")==0) {
        //reject
        enterLoginSubstate(rh->gui->loginState,0);
    }
    else {
        char *token;
        token=strtok(repl,SPLIT);
        int t=0;
        int getInfo = 0;
        int x=250;
        int y=250;
        while( token != NULL ) {
            if (strcmp(token,HALT)==0) {
                t=0;
                token = strtok(NULL, SPLIT);
                continue;
            }
            if (t==0) { //first word in packet
                if (strcmp(token,PLAYER_INFO_RESPONSE)==0) {
                    printf("trying to update player info\n");
                    getInfo=1;
                }
                else if (strcmp(token,"successlogin")==0) {
                    initGameState(rh->gui->gameState,rh->gui->loginState->stateRenderer);
                    deleteLoginState(rh->gui->loginState);
                    *(rh->gui->currentState) = 1;
                    printf("enter the game!!!!!\n");
                }
                else if (strcmp(token,"createnewprofile")==0) {
                    printf("MAKE A NEW PROFILE!!!!!\n");
                    initGameState(rh->gui->gameState,rh->gui->loginState->stateRenderer);
                    deleteLoginState(rh->gui->loginState);
                    *(rh->gui->currentState) = 1;
                }
                else {
                    printf("unsupported command in packet\n");
                }
            }
            if (t==1) {
                if (getInfo) {
                    x=strtol(token,NULL,10);
                }
            }
            if (t==2) {
                if (getInfo) {
                    y=strtol(token,NULL,10);
                    printf("setting player coods\n");
                    setPlayerCoordinates(rh->gui->gameState->you,x,y);
                }
            }
            token = strtok(NULL, SPLIT);
            t++;
        }
    }

}

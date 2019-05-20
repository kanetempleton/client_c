#include "HandleReplies.h"
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
    }
    if (strcmp(repl,"createprofile")==0) {
        //enter the game
        printf("MAKE A NEW PROFILE!!!!!\n");
    }
    if (strcmp(repl,"invalidlogin")==0) {
        //reject
        printf("boobs!!!!\n");
        enterLoginSubstate(rh->gui->loginState,0);
    }
}

#include "HandleReplies.h"
#include "Codes.h"
#include "SendMessage.h"
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
        int getID = 0;
        int updatePos = 0;
        int getMap = 0;
        int showPlr = 0;
        int showX = 0;
        int showY = 0;
        int oldX = 0;
        int oldY = 0;
        int hideID = -1;
        int hidePlayer = 0;
        int showPlayerID = -1;
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
                else if (strcmp(token,SEND_PLAYER_MAP)==0) {
                    getMap = 1;
                }
                else if (strcmp(token,SEND_PLAYER_ID)==0) {
                    getID = 1;
                }
                else if (strcmp(token,SEND_PLAYER_COORDS)==0) {
                    updatePos = 1;
                }
                else if (strcmp(token,LOGOUT_PLAYER)==0) {
                    initLoginState(rh->gui->loginState,rh->gui->gameState->stateRenderer);
                    deleteGameState(rh->gui->gameState);
                    *(rh->gui->currentState) = 0;
                    resetPlayer(yourPlayer);
                }
                else if (strcmp(token,SHOW_PLAYER)==0) {
                    showPlr=1;
                }
                else if (strcmp(token,HIDE_PLAYER)==0) {
                    hidePlayer = 1;
                }
                /*else if (strcmp(token,"successlogin")==0) {
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
                }*/
            }
            if (t==1) {
                if (getInfo || updatePos) {
                    x=strtol(token,NULL,10);
                }
                if (getID) {
                    int id = strtol(token,NULL,10);
                    *(yourPlayer->playerId) = id;
                    messageToServer(PLAYER_INFO_REQUEST);
                }
                else if (getMap) {
                    getMap = strtol(token,NULL,10);
                }
                else if (showPlr) {
                    showPlayerID = strtol(token,NULL,10);
                    //showX = strtol(token,NULL,10);
                }
                else if (hidePlayer) {
                    hideID = strtol(token,NULL,10);
                }
            }
            if (t==2) {
                if (getInfo) {
                    y=strtol(token,NULL,10);
                    printf("setting player coords1\n");
                    int sec = computeMapDataSection(x,y);
                    *(yourPlayer->mapSection) = sec;
                    setPlayerCoordinates(yourPlayer,x,y);
                    initGameState(rh->gui->gameState,rh->gui->loginState->stateRenderer);
                    deleteLoginState(rh->gui->loginState);
                    *(rh->gui->currentState) = 1;
                    sendInitialMapRequest();
                }
                else if (updatePos) {
                    y=strtol(token,NULL,10);
                    printf("setting player coords2\n");
                    setPlayerCoordinates(yourPlayer,x,y);
                    if (x%MAP_WIDTH==0||x%MAP_WIDTH==(MAP_WIDTH-1)||
                        y%MAP_HEIGHT==0||y%MAP_HEIGHT==(MAP_HEIGHT-1)) {
                        int sec = computeMapDataSection(x,y);
                        if (sec!=*(yourPlayer->mapSection)) {
                            *(yourPlayer->mapSection) = sec;
                            clearRenderMapData(rh->gui->gameState->gameMap);
                            sendInitialMapRequest();
                        }

                    }
                }
                else if (getMap==5) {
                    updateMapString(rh->gui->gameState->gameMap,token);
                    /*for (int i=0; i<12; i++) {
                        *(rh->gui->gameState->gameMap->mapstring+i) = token[i];
                    }*/
                    //strcpy(rh->gui->gameState->gameMap->mapstring,token);
                }
                else if (showPlr) {
                    showX = strtol(token,NULL,10);
                }
                else if (hidePlayer) {
                    showX = strtol(token,NULL,10);
                }
            }
            if (t==3) {
                if (showPlr) {
                    showY = strtol(token,NULL,10);
                }
                else if (hidePlayer) {
                    showY = strtol(token,NULL,10);
                    *(rh->gui->gameState->gameMap->rendPlayers[showX%MAP_WIDTH][showY%MAP_HEIGHT])=-1;
                }
            }
            if (t==4) {
                if (showPlr) {
                    oldX = strtol(token,NULL,10);
                }
            }
            if (t==5) {
                if (showPlr) {
                    oldY = strtol(token,NULL,10);
                    if (showPlayerID!=*(yourPlayer->playerId)) {
                        if ((showX/MAP_WIDTH)==((*(yourPlayer->absX))/MAP_WIDTH) &&
                            (showY/MAP_HEIGHT)==((*(yourPlayer->absY))/MAP_HEIGHT)) {
                                printf("player is in your box[%d,%d]\n",showX%MAP_WIDTH,showY%MAP_HEIGHT);
                                *(rh->gui->gameState->gameMap->rendPlayers[oldX%MAP_WIDTH][oldY%MAP_HEIGHT])=-1;
                                *(rh->gui->gameState->gameMap->rendPlayers[showX%MAP_WIDTH][showY%MAP_HEIGHT])=1;
                            }
                    }
                }
            }
            token = strtok(NULL, SPLIT);
            t++;
        }
    }

}

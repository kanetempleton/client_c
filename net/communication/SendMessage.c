#include "SendMessage.h"
#include "Codes.h"

/* messageToServer(c,p,m)
    m: split using SPLIT in codes.h
*/
void messageToServer(char* msg) {
    //pthread_mutex_lock(&guiLock);
    //pthread_mutex_lock(&clientLock);
    char* toSend = malloc(sizeof(char)*(strlen(msg)+strlen(CLIENT_SIGNATURE)+strlen(SPLIT)*2+6));
    strcpy(toSend,CLIENT_SIGNATURE);
    strcat(toSend,SPLIT);
    char idbuf[5];
    sprintf(idbuf,"%d",*(yourPlayer->playerId));
    strcat(toSend,idbuf);
    strcat(toSend,SPLIT);
    strcat(toSend,msg);
    sendMessage(toSend);
    free(toSend);
    //pthread_mutex_unlock(&guiLock);
    //pthread_mutex_unlock(&clientLock);
}


void sendLoginRequest(Player * p, char* user, char* pass) {
    if (strlen(user)==0 || strlen(pass)==0)
        return;
    int numchars = strlen(user)+strlen(pass)+strlen(SEND_LOGIN_REQUEST)+strlen(SPLIT)*2;
    char* sendTxt = malloc(sizeof(char)*(numchars + 1));
    strcpy(p->playerName,user);
    strcpy(sendTxt,SEND_LOGIN_REQUEST);
    strcat(sendTxt,SPLIT);
    strcat(sendTxt,user);
    strcat(sendTxt,SPLIT);
    strcat(sendTxt,pass);//you should encrypt this at some point
    //strcat(sendTxt,HALT); //will add halt later
    //sendMessage(sendTxt);
    messageToServer(sendTxt);
    free(sendTxt);
}

void sendPlayerInfoRequest() {
    sendMessage(PLAYER_INFO_REQUEST);
}
void sendLogoutRequest() {
    messageToServer(PLAYER_LOGOUT_REQUEST);
}


void sendUpdatePlayerCoordinatesRequest(int newX, int newY) {
    char* sendText = malloc(sizeof(char)*(strlen(SPLIT)*2+strlen(PLAYER_MOVEMENT_REQUEST)+20));
    strcpy(sendText,PLAYER_MOVEMENT_REQUEST);
    strcat(sendText,SPLIT);
    char xbuf[4];
    char ybuf[4];
    sprintf(xbuf,"%d",newX);
    sprintf(ybuf,"%d",newY);
    strcat(sendText,xbuf);
    strcat(sendText,SPLIT);
    strcat(sendText,ybuf);
    messageToServer(sendText);
    free(sendText);
}

void sendInitialMapRequest() {
    messageToServer(PLAYER_LOGIN_MAP_REQUEST);
}

void submitMapEdit(char* m) {
    printf("submitting map edit %s\n",m);
    int sec = computeMapDataSection(*(yourPlayer->absX),*(yourPlayer->absY));
    char* sendText = malloc(sizeof(char)*(strlen(SPLIT)*2+strlen(SEND_MAP_EDIT)+32));
    strcpy(sendText,SEND_MAP_EDIT);
    strcat(sendText,SPLIT);
    char secBuf[12];
    sprintf(secBuf,"%d",sec);
    strcat(sendText,secBuf);
    strcat(sendText,SPLIT);
    strcat(sendText,m);
    messageToServer(sendText);
    free(sendText);
    printf("finished map edit submission\n");
}

void sendPublicChat(char* m) {
    //int sec = computeMapDataSection(*(yourPlayer->absX),*(yourPlayer->absY));
    char* sendText = malloc(sizeof(char)*(strlen(SPLIT)+strlen(m)+strlen(SEND_PUBLIC_CHAT)+2));
    strcpy(sendText,SEND_PUBLIC_CHAT);
    strcat(sendText,SPLIT);
    strcat(sendText,m);
    messageToServer(sendText);
    free(sendText);
}

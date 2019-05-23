#include "Codes.h"
#include "../client.h"
#include <string.h>
#include <stdlib.h>

void sendLoginRequest(char* user, char* pass) {
    if (strlen(user)==0 || strlen(pass)==0)
        return;
    int numchars = strlen(user)+strlen(pass)+strlen(SEND_LOGIN_REQUEST)+strlen(SPLIT)*2;
    char* sendTxt = malloc(sizeof(char)*(numchars + 1));
    strcpy(sendTxt,SEND_LOGIN_REQUEST);
    strcat(sendTxt,SPLIT);
    strcat(sendTxt,user);
    strcat(sendTxt,SPLIT);
    strcat(sendTxt,pass);//you should encrypt this at some point
    //strcat(sendTxt,HALT); //will add halt later
    sendMessage(sendTxt);
    free(sendTxt);
}

void sendPlayerInfoRequest() {
    /*int numchars = strlen(user)+strlen(SPLIT)+strlen(PLAYER_INFO_REQUEST);
    char* sendTxt = malloc(sizeof(char)*(numchars + 1));
    strcpy(sendTxt,PLAYER_INFO_REQUEST);
    strcat(sendTxt,SPLIT);
    strcat(sendTxt,user);*/
    sendMessage(PLAYER_INFO_REQUEST);
    //free(sendTxt);
}

void sendUpdatePlayerCoordinatesRequest(Player * p, int newX, int newY) {
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
    printf("gonna send [%s]\n",sendText);
    sendMessage(sendText);
    free(sendText);
}

#include "Codes.h"
#include "../client.h"
#include <string.h>
#include <stdlib.h>

void sendLoginRequest(char* user, char* pass) {
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

#ifndef H_SENDMESSAGE
#define H_SENDMESSAGE
#include "../client.h"
void messageToServer(char* m);
void sendLoginRequest();
void sendPlayerInfoRequest();
void sendUpdatePlayerCoordinatesRequest(int x, int y);
void sendLogoutRequest();
void sendInitialMapRequest();
void submitMapEdit(char* m);
#endif

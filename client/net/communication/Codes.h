#ifndef H_CODES
#define H_CODES
#include "../../gfx/state/game/entity/Player.h"
#define SPLIT ";+;"
#define HALT ";!;"
#define SEND_LOGIN_REQUEST "logmein"
#define PLAYER_INFO_REQUEST "getmyinfo"
#define PLAYER_INFO_RESPONSE "heresdata"
#define PLAYER_MOVEMENT_REQUEST "moveme"
void sendLoginRequest(char* user, char* pass);
void sendPlayerInfoRequest();
void sendUpdatePlayerCoordinatesRequest(Player*p,int x, int y);
#endif

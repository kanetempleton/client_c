#ifndef H_CODES
#define H_CODES
#include "../../gfx/state/game/entity/Player.h"
#include "SendMessage.h"

#define CLIENT_SIGNATURE "808080"
#define SPLIT ";+;"
#define HALT ";!;"

//actions - to server
#define SEND_LOGIN_REQUEST "logmein" //500
#define PLAYER_INFO_REQUEST "getmyinfo" //501
#define PLAYER_MOVEMENT_REQUEST "moveme" //502
#define PLAYER_LOGOUT_REQUEST "logmeout" //503
#define PLAYER_LOGIN_MAP_REQUEST "510"
#define SEND_MAP_EDIT "512"
#define SEND_PUBLIC_CHAT "514"


//actions - from server
#define SEND_PLAYER_ID "heresyourid" //504
#define PLAYER_INFO_RESPONSE "heresdata" //505
#define SEND_PLAYER_COORDS "herescoords" //506
#define KICK_PLAYER "gtfo" //507
#define LOGOUT_PLAYER "bye" //508
#define SHOW_PLAYER "hereis" //509
#define SEND_PLAYER_MAP "511"
#define HIDE_PLAYER "hereisnt"
#define SEND_INFOBOX_MSG "513"
#define PUBLIC_CHAT_FROM "515"

#endif

#ifndef H_CLIENT
#define H_CLIENT
#include "../gfx/GUI.h"
#include "communication/HandleReplies.h"
typedef struct {
    int * id;
    ReplyHandler* replyHandler;
} Client;
Client * newClient();
void initClient(Client * me, ReplyHandler* rh, int assign);
void * startClient(void * arg); //for multithreading
void yellAt(GUI * g, int flag);
void signalGUI(int flag);
void shutDownClient();
void sendMessage(char* send);
#endif

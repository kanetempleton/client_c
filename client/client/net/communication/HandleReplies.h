#ifndef H_HANDLEREPLIES
#define H_HANDLEREPLIES
#include "../../gfx/GUI.h"
typedef struct {
    GUI * gui;
} ReplyHandler;
ReplyHandler* newReplyHandler();
void initReplyHandler(ReplyHandler* rh, GUI* g);
void deleteReplyHandler(ReplyHandler* rh);
void handleReply(ReplyHandler* rh, char * repl);
#endif

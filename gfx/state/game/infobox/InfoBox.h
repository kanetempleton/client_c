#ifndef H_INFOBOX
#define H_INFOBOX
#include "SDL2/SDL.h"
#include "../../../SpriteCache.h"
#include "../../../component/button.h"
#include "../../../text/KeyboardHandler.h"

#define INFOBOX_SIZE 13
#define INFOBOX_FROM_SIZE 12

#define INFOBOX_BUTTON_INDEX 70

//sprites
#define INFOBOX_NAME_TEXT 1
#define INFOBOX_UP_BUTTON 2
#define INFOBOX_DOWN_BUTTON 3
#define INFOBOX_DATA_TEXT_INDEX 4

#define INFOBOX_NUM_BUTTONS 2

typedef struct {
    int * num;
    char* data;
    char* from;
    GameSprite* fromSprite;
} InfoEntry;

typedef struct {
    InfoEntry* messages[INFOBOX_SIZE];
    int* numMessages;
    Button* buttons[INFOBOX_NUM_BUTTONS];
    int* scrollOffset;
    TextInput* gameText;
    GameSprite* textSprite;
} InfoBox;

InfoBox* gameInfoBox;
InfoEntry* newInfoEntry();
InfoBox* newInfoBox();
void initInfoEntry(InfoEntry* e, int datasize);
void initInfoBox(InfoBox* b);
void deleteInfoEntry(InfoEntry* e);
void deleteInfoBox(InfoBox* b);
void addEntryToInfoBox(InfoBox* b, char* from, char* msg);
void renderInfoBox(InfoBox* b, SDL_Renderer* r);
void processClicks_infoBox(InfoBox* b, int clickX, int clickY);
void processKeys_infoBox(InfoBox* b, int keyId);
#endif

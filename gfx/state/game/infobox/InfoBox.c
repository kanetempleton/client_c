//gfx/state/game/infobox/InfoBox.c
#include "InfoBox.h"
#include "../../../GUI.h"
#include <stdlib.h>
#include "../../../../net/communication/SendMessage.h"

InfoEntry* newInfoEntry() {
    return (InfoEntry*)malloc(sizeof(InfoEntry));
}
InfoBox* newInfoBox() {
    return (InfoBox*)malloc(sizeof(InfoBox));
}
void initInfoEntry(InfoEntry* e,int datasize)  {
    e->num=malloc(sizeof(int));
    e->data=malloc(datasize+1);
    e->from=malloc(INFOBOX_FROM_SIZE+1);
    e->fromSprite = newGameSprite();
    initGameSprite(e->fromSprite,Main_Renderer,"NULL",yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Black));
}
void initInfoBox(InfoBox* b) {
    /*(for (int i=0; i<INFOBOX_SIZE; i++) {
        b->messages[i]=newInfoEntry();
    }*/
    printf("initing infobox\n");
    b->numMessages=malloc(sizeof(int));
    *(b->numMessages)=0;
    setSpriteCoordinates(yourPlayer->guiSprites->infoboxSprites[0],0,TILE_SIZE*MAP_HEIGHT);
    setSpriteDimensions(yourPlayer->guiSprites->infoboxSprites[0],448,192);
    loadTextToSprite(yourPlayer->guiSprites->infoboxSprites[INFOBOX_NAME_TEXT],yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), yourPlayer->playerName);
    setSpriteCoordinates(yourPlayer->guiSprites->infoboxSprites[1],2,550);
    printf("initing buttons\n");
    /*setSpriteCoordinates(yourPlayer->guiSprites->infoboxSprites[INFOBOX_UP_BUTTON],420,390);
    setSpriteCoordinates(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DOWN_BUTTON],420,520);*/
    printf("initing text stuff\n");
    for (int i=0; i<INFOBOX_SIZE; i++) {
        setSpriteCoordinates(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i],90,530-12*i);
        //setSpriteCoordinates(b->messages[i]);
    }
    /*for (int i=0; i<INFOBOX_NUM_BUTTONS; i++) {
        b->buttons[i] = newButton();
        initButton(b->buttons[i],INFOBOX_BUTTON_INDEX+i,416,392+120*i);
        loadButtonImage(b->buttons[i],Main_Renderer);
    }*/
    b->scrollOffset = malloc(sizeof(int));
    *(b->scrollOffset)=0;

    b->gameText = newTextInputField();
    initTextInputField(b->gameText,50);

    b->textSprite = newGameSprite();
    initGameSprite(b->textSprite,Main_Renderer,"NULL",yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Black));
    loadTextToSprite(b->textSprite,Main_Renderer,yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Black),"");
    setSpriteCoordinates(b->textSprite,90,554);
    //loadTextToSprite(GameSprite* s, SDL_Renderer* r, TTF_Font* font, SDL_Color col, char* txt)
    //void initGameSprite(GameSprite* s,SDL_Renderer* r,char* path,TTF_Font* font, SDL_Color col)

    //setSpriteCoordinates(yourPlayer->spriteCache->infoboxSprites[1],);
    //setSpriteCoordinates(yourPlayer->spriteCache->infoboxSprites[1],0,TILE_SIZE*MAP_HEIGHT);

}
void deleteInfoEntry(InfoEntry* e) {
    free(e->num);
    free(e->data);
    free(e->from);
}
void deleteInfoBox(InfoBox* b) {
    for (int i=0; i<INFOBOX_SIZE; i++) {
        deleteInfoEntry(b->messages[i]);
    }
    free(b->numMessages);
}


void addEntryToInfoBox(InfoBox* b, char* from, char* msg) {
    if (*(b->numMessages)>=INFOBOX_SIZE) {
        printf("info box full\n"); //delete message from top
        for (int i=*(b->numMessages)-1; i>0; i--) {
            GameSprite* upper = yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i];
            GameSprite* lower = yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i-1];
            //setSpriteCoordinates(lower,*(upper->absX),*(upper->absY)-12*i);
            loadTextToSprite(upper,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), lower->text);
            //loadTextToSprite(b->messages[i+1]->fromSprite,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), b->messages[i]->fromSprite->text);
        }
        for (int i=0; i<*(b->numMessages)-1; i++) {
            loadTextToSprite(b->messages[i]->fromSprite,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), b->messages[i+1]->fromSprite->text);
        }
        loadTextToSprite(b->messages[*(b->numMessages)-1]->fromSprite,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), from);
        loadTextToSprite(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX],yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), msg);
        return;
    }
    int i = *(b->numMessages);
    b->messages[i] = newInfoEntry();
    initInfoEntry(b->messages[i],strlen(msg));
    *(b->messages[i]->num) = i;
    strcpy(b->messages[i]->data,msg);
    strcpy(b->messages[i]->from,from);
    loadTextToSprite(b->messages[i]->fromSprite,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black),b->messages[i]->from);
    for (int j=0; j<i; j++) {
        setSpriteCoordinates(b->messages[j]->fromSprite,2,*(b->messages[j]->fromSprite->absY)-12);
    }
    setSpriteCoordinates(b->messages[i]->fromSprite,2,530);
    //loadTextToSprite(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+*(b->numMessages)],yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), msg);
    printf("added entry %d to infobox: [%s] %s\n",i,b->messages[i]->from,b->messages[i]->data);
    //*(b->numMessages)=i+1;
    for (int i=*(b->numMessages); i>0; i--) {
        GameSprite* upper = yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i];
        GameSprite* lower = yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i-1];
        //setSpriteCoordinates(lower,*(upper->absX),*(upper->absY)-12*i);
        loadTextToSprite(upper,yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), lower->text);
    }
    loadTextToSprite(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX],yourPlayer->guiSprites->renderer, yourPlayer->guiSprites->AndaleMono, *(yourPlayer->guiSprites->Black), msg);
    *(b->numMessages)=i+1;
}

void renderInfoBox(InfoBox* b, SDL_Renderer* r) {
    //"data/assets/interface/infobox.png";
    renderSprite(yourPlayer->guiSprites->infoboxSprites[0],r);
    renderSprite(yourPlayer->guiSprites->infoboxSprites[1],r);
    //printf(yourPlayer->guiSprites->infoboxSprites);
    for (int i=0; i<*(b->numMessages); i++) {
        renderSprite(yourPlayer->guiSprites->infoboxSprites[INFOBOX_DATA_TEXT_INDEX+i],r);
        renderSprite(b->messages[i]->fromSprite,r);
    }
    /*for (int i=0; i<INFOBOX_NUM_BUTTONS; i++) {
        renderButton(b->buttons[i],r);
    }*/
    renderSprite(b->textSprite,r);
    //renderSprite();

}

void processClicks_infoBox(InfoBox* b, int clickX, int clickY) {
    /*for (int i=0; i<INFOBOX_NUM_BUTTONS; i++) {
        if (clickButton(b->buttons[i],clickX,clickY)) {
            if (i==0) {//up
                printf("scrollin up\n");
                if (*(b->numMessages)>13) {
                    *(b->scrollOffset)=*(b->scrollOffset)+1;
                    printf("scroll offset is now %d\n",*(b->scrollOffset));
                }
            }
            else if (i==1) { //down
                printf("scrollin down\n");
            }
        }
    }*/
}

void processKeys_infoBox(InfoBox* b, int keyid) {
    if (keyid==SDLK_RETURN) {
        printf("send public chat %s\n",b->gameText->build);
        sendPublicChat(b->gameText->build);
        clearTextField(b->gameText);
        setSpriteText(b->textSprite,b->gameText->build);
        //loadTextToSprite(b->textSprite,Main_Renderer,yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Black),"");
    } else {
        addKey(b->gameText,keyid);
        //loadTextToSprite(b->textSprite,Main_Renderer,yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Black),b->gameText->build);
        setSpriteText(b->textSprite,b->gameText->build);
    }
}

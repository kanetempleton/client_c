#include "PlayerInfoMenu.h"
#include <stdlib.h>
#include <stdio.h>

void initPlayerInfoMenu(HUDMenu* men) {
    setSpriteCoordinates(yourPlayer->guiSprites->menu_playerInfoSprites[0],507,75); //info
    setSpriteCoordinates(yourPlayer->guiSprites->menu_playerInfoSprites[1],458,112); //coords
    setSpriteText(yourPlayer->guiSprites->menu_playerInfoSprites[0],"Player Info");
    //setSpriteText(yourPlayer->guiSprites->menu_playerInfoSprites[0],"Player Info");
    *(men->menuData[0]) = *(yourPlayer->absX);
    *(men->menuData[1]) = *(yourPlayer->absY);
    char* fill = malloc(strlen("Coordinates: ,")+10);
    strcpy(fill,"Coordinates: ");
    char* bf = malloc(5);
    sprintf(bf,"%d",*(yourPlayer->absX));
    strcat(fill,bf);
    strcat(fill,",");
    sprintf(bf,"%d",*(yourPlayer->absY));
    strcat(fill,bf);
    free(bf);
    setSpriteText(yourPlayer->guiSprites->menu_playerInfoSprites[1],fill);
    free(fill);
}
void openPlayerInfoMenu(HUDMenu* men) {
    //nothing yet
}
void renderPlayerInfoMenu(HUDMenu* men, SDL_Renderer* r) {
    if (*(yourPlayer->absX)!=*(men->menuData[0]) || *(yourPlayer->absY)!=*(men->menuData[1])) {
        *(men->menuData[0]) = *(yourPlayer->absX);
        *(men->menuData[1]) = *(yourPlayer->absY);
        char* fill = malloc(strlen("Coordinates: ,")+10);
        strcpy(fill,"Coordinates: ");
        char* bf = malloc(5);
        sprintf(bf,"%d",*(yourPlayer->absX));
        strcat(fill,bf);
        strcat(fill,",");
        sprintf(bf,"%d",*(yourPlayer->absY));
        strcat(fill,bf);
        free(bf);
        setSpriteText(yourPlayer->guiSprites->menu_playerInfoSprites[1],fill);
        free(fill);
    }
    for (int i=0; i<MENU_PLAYERINFO_NUM_SPRITES; i++)
        renderSprite(yourPlayer->guiSprites->menu_playerInfoSprites[i]);
}
void processClicks_PlayerInfo(HUDMenu* men, int clickX, int clickY) {

}
void processButtons_PlayerInfo(HUDMenu* men, int id) {

}

#include "HUD.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include "../map/Map.h"
#include "menus/SettingsMenu.h"
#include "../../../GUI.h"
#include "../../../../net/client.h"
#include "../../../../net/communication/SendMessage.h"
#include "menus/PlayerInfoMenu.h"


GameHUD* newHUD() {
    return (GameHUD*)malloc(sizeof(GameHUD));
}
void initHUD(GameHUD* hud, SDL_Renderer* r) {
    hud->activeMenu = malloc(sizeof(int));
    *(hud->activeMenu) = 0;
    for (int i=0; i<NUMBER_OF_MENUS; i++) {
        char* fileName = malloc(3+strlen("data/assets/interface/hud/icons/.png"));
        char* iconNum = malloc(3);
        sprintf(iconNum,"%d",i);
        strcpy(fileName,"data/assets/interface/hud/icons/");
        strcat(fileName,iconNum);
        strcat(fileName,".png");
        SDL_Surface* iconSurf = IMG_Load(fileName);
        hud->menuIcon[i] = SDL_CreateTextureFromSurface(r,iconSurf);
        SDL_FreeSurface(iconSurf);
        free(iconNum);
        free(fileName);

        hud->hudMenu[i] = newHUDMenu();
        initHUDMenu(hud->hudMenu[i],i);
        //hud->hudMenu[i]->renderer = r;
    }

    SDL_Surface* selSurf = IMG_Load("data/assets/interface/hud/selected.png");
    hud->selectIcon = SDL_CreateTextureFromSurface(r,selSurf);
    SDL_FreeSurface(selSurf);

    SDL_Surface* frameSurf = IMG_Load("data/assets/interface/hud/hudframe.png");
    hud->frameImage = SDL_CreateTextureFromSurface(r,frameSurf);
    SDL_FreeSurface(frameSurf);

    initializeAllMenus(hud);

}
void renderHUD(GameHUD* hud, SDL_Renderer* r) {
    SDL_Rect frameRect = {HUD_START_X,HUD_START_Y,HUD_WIDTH,HUD_HEIGHT};
    SDL_Rect selectRect = {HUD_START_X+TILE_SIZE*(*(hud->activeMenu)%(NUMBER_OF_MENUS/2))+1,
                            HUD_START_Y+TILE_SIZE*(*(hud->activeMenu)/(NUMBER_OF_MENUS/2))+1,
                            TILE_SIZE-2,TILE_SIZE-2};

    SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hudframe,NULL,&frameRect);
    SDL_RenderCopy(Main_Renderer,hud->selectIcon,NULL,&selectRect);

    for (int i=0; i<NUMBER_OF_MENUS; i++) {
        SDL_Rect iconRect = {HUD_START_X+TILE_SIZE*(i%(NUMBER_OF_MENUS/2))+1,
                                HUD_START_Y+TILE_SIZE*(i/(NUMBER_OF_MENUS/2))+1,
                                TILE_SIZE-2,TILE_SIZE-2};
        switch (i) {
            case 0:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud0,NULL,&iconRect);
                break;
            case 1:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud1,NULL,&iconRect);
                break;
            case 2:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud2,NULL,&iconRect);
                break;
            case 3:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud3,NULL,&iconRect);
                break;
            case 4:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud4,NULL,&iconRect);
                break;
            case 5:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud5,NULL,&iconRect);
                break;
            case 6:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud6,NULL,&iconRect);
                break;
            case 7:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud7,NULL,&iconRect);
                break;
            case 8:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud8,NULL,&iconRect);
                break;
            case 9:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud9,NULL,&iconRect);
                break;
            case 10:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud10,NULL,&iconRect);
                break;
            case 11:
                SDL_RenderCopy(Main_Renderer,yourPlayer->guiSprites->hud11,NULL,&iconRect);
                break;
        }
        //SDL_RenderCopy(Main_Renderer,hud->menuIcon[i],NULL,&iconRect);
        //SDL_RenderCopy(Main_Renderer,hud->menuIcon2[i],NULL,&iconRect2);
    }
    switch (*(hud->activeMenu)) {
        case SETTINGS_MENU_ID:
            renderSettingsMenu(hud->hudMenu[SETTINGS_MENU_ID],r);
            break;
    }
}
void switchToMenu(GameHUD* hud, int switchTo) {
    *(hud->activeMenu)=switchTo;
    printf("[game menu] switched to %d\n",*(hud->activeMenu));
}
void processClicks_HUD(GameHUD* hud, int clickX, int clickY) {
    if (clickX>=HUD_START_X && clickX<=(HUD_START_X+HUD_WIDTH)
        && clickY >= HUD_START_Y && clickY <= (HUD_START_Y+TILE_SIZE*2)) {
            int spaceNum = (clickX - HUD_START_X)/TILE_SIZE + (NUMBER_OF_MENUS/2)*((clickY - HUD_START_Y)/TILE_SIZE);
            switchToMenu(hud,spaceNum);
            switch (spaceNum) {
                case COMBAT_MENU_ID:
                    printf("[combat menu] Not supported.\n");
                    break;
                case SKILL_MENU_ID:
                    printf("[skill menu] Not supported.\n");
                    break;
                case INVENTORY_MENU_ID:
                    printf("[inventory menu] Not supported.\n");
                    break;
                case EQUIPMENT_MENU_ID:
                    printf("[equipment menu] Not supported.\n");
                    break;
                case ADVENTURE_MENU_ID:
                    printf("[adventure menu] Not supported.\n");
                    break;
                case BLANK1_MENU_ID:
                    printf("[blank menu 1] Not supported.\n");
                    break;
                    //bottom row
                case CHAT_MENU_ID:
                    printf("[chat menu] Not supported.\n");
                    break;
                case MUSIC_MENU_ID:
                    printf("[music menu] Not supported.\n");
                    break;
                case BLANK2_MENU_ID:
                    printf("[blank menu 2] Not supported.\n");
                    break;
                case SETTINGS_MENU_ID:
                    openSettingsMenu(hud->hudMenu[SETTINGS_MENU_ID]);
                    break;
                case PLAYERINFO_MENU_ID:
                    printf("[player info menu] Not supported.\n");
                    break;
                case LOGOUT_MENU_ID:
                    //printf("[logout menu] Not supported.\n");
                    sendLogoutRequest();
                    break;
            }
    }
    switch (*(hud->activeMenu)) {
        case SETTINGS_MENU_ID:
            processClicks_Settings(hud->hudMenu[SETTINGS_MENU_ID],clickX,clickY);
            break;
    }
}




void initializeAllMenus(GameHUD* hud) {
    initSettingsMenu(hud->hudMenu[SETTINGS_MENU_ID]);
    initPlayerInfoMenu(hud->hudMenu[PLAYERINFO_MENU_ID]);
}

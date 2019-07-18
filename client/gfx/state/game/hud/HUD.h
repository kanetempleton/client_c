#ifndef H_HUD
#define H_HUD
#include "SDL2/SDL.h"
#include "HUDMenu.h"

#define NUMBER_OF_MENUS 12
#define HUD_START_X 448
#define HUD_START_Y 0
#define HUD_WIDTH 192
#define HUD_HEIGHT 384

//top row
#define COMBAT_MENU_ID 0
#define SKILL_MENU_ID 1
#define INVENTORY_MENU_ID 2
#define EQUIPMENT_MENU_ID 3
#define ADVENTURE_MENU_ID 4
#define BLANK1_MENU_ID 5 //needs something
//bottom row
#define CHAT_MENU_ID 6
#define MUSIC_MENU_ID 7
#define BLANK2_MENU_ID 8 //needs something
#define SETTINGS_MENU_ID 9
#define PLAYERINFO_MENU_ID 10
#define LOGOUT_MENU_ID 11

typedef struct {
    int * activeMenu;
    SDL_Texture* menuIcon[NUMBER_OF_MENUS];
    SDL_Texture* menuIcon2[NUMBER_OF_MENUS];
    SDL_Texture* selectIcon;
    SDL_Texture* frameImage;
    HUDMenu* hudMenu[NUMBER_OF_MENUS];
} GameHUD;

GameHUD* newHUD();
void initHUD(GameHUD* hud, SDL_Renderer* r);
void deleteHUD(GameHUD* hud);
void renderHUD(GameHUD* hud, SDL_Renderer* r);
void switchToMenu(GameHUD* hud, int switchTo);
void processClicks_HUD(GameHUD* hud, int clickX, int clickY);
void initializeAllMenus(GameHUD* hud);
#endif

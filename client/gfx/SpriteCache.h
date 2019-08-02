#ifndef H_SPRITECACHE
#define H_SPRITECACHE
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#define INFOBOX_NUM_SPRITES 17
#define MENU_PLAYERINFO_NUM_SPRITES 2

typedef struct {
    SDL_Texture* texture;
    int* loaded;
    int* absX;
    int* absY;
    int* width;
    int* height;
    int* visible;

    char* text;
    TTF_Font* font;
    SDL_Color* color;
    //int* spriteID;
} GameSprite;

typedef struct {
    SDL_Texture* hud0;
    SDL_Texture* hud1;
    SDL_Texture* hud2;
    SDL_Texture* hud3;
    SDL_Texture* hud4;
    SDL_Texture* hud5;
    SDL_Texture* hud6;
    SDL_Texture* hud7;
    SDL_Texture* hud8;
    SDL_Texture* hud9;
    SDL_Texture* hud10;
    SDL_Texture* hud11;
    SDL_Texture* hudframe;

    SDL_Texture* gameCursor;

    SDL_Renderer* renderer;

    GameSprite* infoboxSprites[INFOBOX_NUM_SPRITES];

    //user interface
    GameSprite* menu_playerInfoSprites[MENU_PLAYERINFO_NUM_SPRITES];

    TTF_Font* Arial;
    TTF_Font* AndaleMono;
    SDL_Color* White;
    SDL_Color* Black;

} SpriteCache;

GameSprite* newGameSprite();
SpriteCache* newSpriteCache();
void initGameSprite(GameSprite* s,SDL_Renderer* r, char* path,TTF_Font* font, SDL_Color col); //pass NULL to path for text sprites
void removeGameSprite(GameSprite* s);
void initializeSpriteCache(SpriteCache* s, SDL_Renderer* r);

void setSpriteCoordinates(GameSprite* s, int x, int y);
void setSpriteDimensions(GameSprite* s, int w, int h);
void showSprite(GameSprite* s);
void hideSprite(GameSprite* s);

char* infoBox_getSpritePath(int id);

void renderSprite(GameSprite* s, SDL_Renderer* r);

void loadTextToSprite(GameSprite* s, SDL_Renderer* r, TTF_Font* font, SDL_Color col, char* txt);
void setSpriteText(GameSprite* s, char* txt);
#endif

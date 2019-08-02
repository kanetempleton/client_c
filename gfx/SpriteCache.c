#include "SpriteCache.h"
#include <stdlib.h>
#include "SDL2/SDL_image.h"
#include "GUI.h"

GameSprite* newGameSprite() {
    return (GameSprite*)malloc(sizeof(GameSprite));
}

SpriteCache* newSpriteCache() {
    return (SpriteCache*)malloc(sizeof(SpriteCache));
}

void initGameSprite(GameSprite* s,SDL_Renderer* r,char* path,TTF_Font* font, SDL_Color col) {

    s->loaded=malloc(sizeof(int));
    s->absX = malloc(sizeof(int));
    s->absY = malloc(sizeof(int));
    s->width = malloc(sizeof(int));
    s->height = malloc(sizeof(int));
    s->visible = malloc(sizeof(int));
    *(s->absX) = -1;
    *(s->absY) = -1;
    *(s->width) = -1;
    *(s->height) = -1;
    *(s->visible) = 0;
    s->text = malloc(25);
    s->font = malloc(sizeof(TTF_Font*));
    s->color = malloc(sizeof(SDL_Color));
    if (strcmp(path,"NULL")==0) {
        printf("NULLPAth\n");
        SDL_Surface* spriteSurf = TTF_RenderText_Solid(font,"",col);
        s->texture = SDL_CreateTextureFromSurface(r,spriteSurf);
        SDL_FreeSurface(spriteSurf);
        strcpy(s->text,"");
        s->font = font;
        *(s->color) = col;
        *(s->loaded)=1;
    }
    else {
        SDL_Surface* spriteSurf = IMG_Load(path);
        s->texture = SDL_CreateTextureFromSurface(r,spriteSurf);
        SDL_FreeSurface(spriteSurf);
        strcpy(s->text,"");
        s->font = font;
        *(s->color) = col;
        //SDL_QueryTexture(s->texture, NULL, NULL, &*(s->height), &(s->width));
        //SDL_QueryTexture(s->texture, NULL, NULL, &*(s->height), &*(s->width));
        *(s->loaded)=1;
    }
}

void setSpriteCoordinates(GameSprite* s, int x, int y) {
    *(s->absX) = x;
    *(s->absY) = y;
}
void setSpriteDimensions(GameSprite* s, int w, int h) {
    *(s->width) = w;
    *(s->height) = h;
}
void showSprite(GameSprite* s) {
    *(s->visible)=1;
}
void hideSprite(GameSprite* s) {
    *(s->visible)=0;
}

void initializeSpriteCache(SpriteCache* s, SDL_Renderer* r) {
    printf("initializing sprites\n");
    SDL_Surface* loadSurf;



    s->Arial = malloc(sizeof(TTF_Font*));
    s->AndaleMono = malloc(sizeof(TTF_Font*));
    s->White = malloc(sizeof(SDL_Color));
    s->Black = malloc(sizeof(SDL_Color));
    s->Arial = TTF_OpenFont("data/assets/fonts/Arial.ttf",16);
    s->AndaleMono = TTF_OpenFont("data/assets/fonts/AndaleMono.ttf",12);

    SDL_Color white = {255,255,255};
    SDL_Color black = {0,0,0};
    *(s->White) = white;
    *(s->Black) = black;

    for (int i=0; i<INFOBOX_NUM_SPRITES; i++) {
    //    loadSurf = IMG_Load("data/assets/interface/hud/icons/0.png");
        s->infoboxSprites[i]=newGameSprite();
        initGameSprite(s->infoboxSprites[i],r,infoBox_getSpritePath(i),s->Arial,*(s->Black));
    }

    for (int i=0; i<MENU_PLAYERINFO_NUM_SPRITES; i++) {
        s->menu_playerInfoSprites[i]=newGameSprite();
        initGameSprite(s->menu_playerInfoSprites[i],r,"NULL",s->Arial,*(s->Black));
    }

    //lololol please ignore this
    loadSurf = IMG_Load("data/assets/interface/hud/icons/0.png");
    s->hud0 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/1.png");
    s->hud1 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/2.png");
    s->hud2 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/3.png");
    s->hud3 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/4.png");
    s->hud4 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/5.png");
    s->hud5 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/6.png");
    s->hud6 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/7.png");
    s->hud7 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/8.png");
    s->hud8 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/9.png");
    s->hud9 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/10.png");
    s->hud10 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("data/assets/interface/hud/icons/11.png");
    s->hud11 = SDL_CreateTextureFromSurface(Main_Renderer,loadSurf);
    SDL_FreeSurface(loadSurf);

    SDL_Surface* loadS5urf = IMG_Load("data/assets/interface/hud/hudframe.png");
    s->hudframe = SDL_CreateTextureFromSurface(Main_Renderer,loadS5urf);
    SDL_FreeSurface(loadS5urf);

    s->renderer=r;
}



char* infoBox_getSpritePath(int id) {
    switch (id) {
        case 0:
            return "data/assets/interface/infobox/infobox2.png";
        case 2: //up button
            return "data/assets/buttons/70.png";
        case 3: //down button
            return "data/assets/buttons/71.png";
        case 1: //text sprites
            return "NULL";
        default:
            return "NULL";
    }
    return "data/assets/interface/infobox/up.png";
}

void renderSprite(GameSprite* s, SDL_Renderer* r) {
    SDL_Rect rendAt = {*(s->absX),*(s->absY),*(s->width),*(s->height)};
    SDL_RenderCopy(r,s->texture,NULL,&rendAt);
}

void loadTextToSprite(GameSprite* s, SDL_Renderer* r, TTF_Font* font, SDL_Color col, char* txt) {
    SDL_Surface* spriteSurf = TTF_RenderText_Solid(font,txt,col);
    s->texture = SDL_CreateTextureFromSurface(r,spriteSurf);
    strcpy(s->text,txt);
    //s->text = txt;
    s->font = font;
    *(s->color) = col;
    SDL_FreeSurface(spriteSurf);
    TTF_SizeText(font,txt,&(*(s->width)),&(*(s->height)));
}

void setSpriteText(GameSprite* s, char* txt) {
    loadTextToSprite(s,Main_Renderer,s->font,*(s->color),txt);
}

#ifndef H_SPRITECACHE
#define H_SPRITECACHE
#include "SDL2/SDL.h"

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

    SDL_Renderer* spriteRenderer;
} SpriteCache;

SpriteCache* newSpriteCache();
void initializeSpriteCache(SpriteCache* s, SDL_Renderer* r);
#endif

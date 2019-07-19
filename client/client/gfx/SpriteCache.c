#include "SpriteCache.h"
#include <stdlib.h>
#include "SDL2/SDL_image.h"
#include "GUI.h"

SpriteCache* newSpriteCache() {
    return (SpriteCache*)malloc(sizeof(SpriteCache));
}

void initializeSpriteCache(SpriteCache* s, SDL_Renderer* r) {
    printf("initializing sprites\n");
    SDL_Surface* loadSurf;

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

    s->spriteRenderer=r;
}

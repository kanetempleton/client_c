#ifndef H_NPC
#define H_NPC
#include "SDL2/SDL.h"
#include "../../../SpriteCache.h"
#define NUM_NPC_CLICK_OPTIONS 2
typedef struct {
    int* id;
    int* memID;
    int* x;
    int* y;
    int* z;
    SDL_Texture* texture;
    GameSprite* nameSprite;
    char* name;
    int* visible;
    int* powLvl;
    int* options[NUM_NPC_CLICK_OPTIONS];
} NPC;

NPC* newNPC();
void initNPC(NPC* n, int id, char* name);
void deleteNPC(NPC* n);
void setNPCCoords(NPC* n, int absX, int absY, int absZ);
void setNPCTexture(NPC* n, SDL_Renderer* r, char* path);
void renderNPC(NPC* n, SDL_Renderer* r);

void setNPCVisibility(NPC* n, int vis);
void clickNPC(NPC* n, int x, int y);
void setNPCMemoryID(NPC* n, int did);
void enableNPCClickOption(NPC* n, int op);
void disableNPCClickOption(NPC* n, int op);
void setNPCLevel(NPC* n, int lvl);
#endif

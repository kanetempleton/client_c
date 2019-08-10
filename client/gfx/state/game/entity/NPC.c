#include "NPC.h"
#include <stdlib.h>
#include "SDL2/SDL_image.h"
#include "../map/Map.h"
#include <string.h>
#include "../../../GUI.h"

NPC* newNPC() {
    return (NPC*)malloc(sizeof(NPC));
}

void initNPC(NPC* n, int id, char* name) {
    n->id=malloc(sizeof(int));
    n->x=malloc(sizeof(int));
    n->y=malloc(sizeof(int));
    n->z=malloc(sizeof(int));
    n->visible=malloc(sizeof(int));
    n->name = malloc(strlen(name)+1);
    n->memID = malloc(sizeof(int));
    n->powLvl = malloc(sizeof(int));
    for (int i=0; i<NUM_NPC_CLICK_OPTIONS; i++) {
        n->options[i]=malloc(sizeof(int));
        *(n->options[i])=0;
    }
    *(n->memID)=-1;
    *(n->id)=id;
    *(n->x)=-1;
    *(n->y)=-1;
    *(n->z)=-1;
    *(n->visible)=0;
    *(n->powLvl)=0;
    char* path = malloc(strlen("data/assets/entity/npc/.png")+6);
    strcpy(path,"data/assets/entity/npc/");
    char* buf = malloc(5);
    sprintf(buf,"%d",id);
    strcat(path,buf);
    strcat(path,".png");
    setNPCTexture(n,Main_Renderer,path);
    printf("loaded image from %s\n",path);
    free(path);
    free(buf);
    strcpy(n->name,name);

    n->nameSprite = newGameSprite();
    initGameSprite(n->nameSprite,Main_Renderer,"NULL",yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Cyan));
    char* namePlusLvl = malloc(strlen(name)+10);
    strcpy(namePlusLvl,name);
    strcat(namePlusLvl," Lvl ");
    char* lvBuf = malloc(10);
    sprintf(lvBuf,"%d",*(n->powLvl));
    strcat(namePlusLvl,lvBuf);
    loadTextToSprite(n->nameSprite,Main_Renderer,yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Cyan),namePlusLvl);
    free(lvBuf);
    free(namePlusLvl);

}

void deleteNPC(NPC* n) {
    free(n->id);
    free(n->x);
    free(n->y);
    free(n->z);
    free(n->visible);
    free(n->powLvl);
    for (int i=0; i<NUM_NPC_CLICK_OPTIONS; i++) {
        free(n->options[i]);
    }
    SDL_DestroyTexture(n->texture);
}
void setNPCCoords(NPC* n, int absX, int absY, int absZ) {
    *(n->x)=absX;
    *(n->y)=absY;
    *(n->z)=absZ;
    setSpriteCoordinates(n->nameSprite,TILE_SIZE*(*(n->x)%MAP_WIDTH)-3 ,TILE_SIZE*(*(n->y)%MAP_HEIGHT)-12);
}
void setNPCTexture(NPC* n, SDL_Renderer* r, char* path) {
    SDL_Surface* surf = IMG_Load(path);
    n->texture = SDL_CreateTextureFromSurface(r,surf);
    SDL_FreeSurface(surf);
    *(n->visible)=1;
}
void renderNPC(NPC* n, SDL_Renderer* r) {
    if (*(n->visible)) {
        //printf("rendering npc %d coords %d %d\n",*(n->id),*(n->x),*(n->y));
        SDL_Rect npcrect = {TILE_SIZE*(*(n->x)%MAP_WIDTH),TILE_SIZE*(*(n->y)%MAP_HEIGHT),TILE_WIDTH,TILE_HEIGHT};
        SDL_RenderCopy(r,n->texture,NULL,&npcrect);
        renderSprite(n->nameSprite,r);
    }
}

void setNPCVisibility(NPC* n, int vis) {
    *(n->visible)=vis;
}

void clickNPC(NPC* n, int x, int y) {
    int scrClickX = x/TILE_SIZE;
    int scrClickY = y/TILE_SIZE;
    int scrNpcX = *(n->x)%MAP_WIDTH;
    int scrNpcY = *(n->y)%MAP_HEIGHT;
    if (scrClickX==scrNpcX && scrClickY==scrNpcY) {
        printf("NPC clicked %d\n",*(n->id));
    }
}

void setNPCMemoryID(NPC* n, int did) {
    *(n->memID)=did;
}

void enableNPCClickOption(NPC* n, int op) {
    if (op>=NUM_NPC_CLICK_OPTIONS)
        return;
    printf("[NPC] enabled option %d for npc %s\n",op,n->name);
    *(n->options[op])=1;
}

void disableNPCClickOption(NPC* n, int op) {
    if (op>=NUM_NPC_CLICK_OPTIONS)
        return;
    *(n->options[op])=0;
}

void setNPCLevel(NPC* n, int lvl) {
    if (n!=NULL) {
        printf("[NPC]setting power level to %d for %s\n",lvl,n->name);
        *(n->powLvl)=lvl;
        char* namePlusLvl = malloc(strlen(n->name)+10);
        strcpy(namePlusLvl,n->name);
        strcat(namePlusLvl," Lvl ");
        char* lvBuf = malloc(10);
        sprintf(lvBuf,"%d",*(n->powLvl));
        strcat(namePlusLvl,lvBuf);
        loadTextToSprite(n->nameSprite,Main_Renderer,yourPlayer->guiSprites->AndaleMono,*(yourPlayer->guiSprites->Cyan),namePlusLvl);
        free(lvBuf);
        free(namePlusLvl);
    }

}

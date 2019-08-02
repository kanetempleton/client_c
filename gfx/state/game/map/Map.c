#include "Map.h"
#include "../../../GUI.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Map* newMap() {
    return (Map*)malloc(sizeof(Map));
}

int loadTile(Map* m, char* dataChunk) {
    int alreadyLoaded = 0;
    for (int i=0; i<*(m->loadedTileCount); i++) {
        if (strcmp(m->tileCache[i]->tileData,dataChunk)==0) {
            //printf("tile %s has already been loaded\n",dataChunk);
            alreadyLoaded = 1;
            return i;
        }
    }
    if (!alreadyLoaded) {
        printf("preparing to load %s to tile %d\n",dataChunk,*(m->loadedTileCount));
        loadDataToTile(m->tileCache[*(m->loadedTileCount)],dataChunk,m->renderer);
        *(m->loadedTileCount)=*(m->loadedTileCount)+1;
        return *(m->loadedTileCount)-1;
    }
    return 0; //put new tiles at beginning

    //TODO: this will fuck up once all tiles have been loaded


    /*char* filepath = malloc(strlen("data/assets/map/.png")+TILE_DATA_SIZE+strlen(dataChunk)+8);
    strcpy(filepath,"data/assets/map/");
    strcat(filepath,dataChunk);
    strcat(filepath,".png");
    SDL_Surface* tileSurface = IMG_Load(filepath);
    m->tileTexture[relX][relY] = SDL_CreateTextureFromSurface(m->renderer,tileSurface);
    //printf("made %d,%d = %s\n",relX,relY,filepath);
    SDL_FreeSurface(tileSurface);
    free(filepath);*/
}

int computeMapDataSection(int x, int y) {
    int mapSectionX = x/MAP_WIDTH;
    int mapSectionY = y/MAP_HEIGHT;
    int offsetSectionX = mapSectionX + 714; //(MAX_COORDINATE/MAP_WIDTH);
    int offsetSectionY = mapSectionY + 833; //(MAX_COORDINATE/MAP_HEIGHT);
    int sumPartX =  offsetSectionX * 10000;
    int sumPartY = offsetSectionY + 100000000;
    return sumPartX+sumPartY;
}

void initMap(Map* m, SDL_Renderer* r) {
    printf("initializing map... ");
    m->mapstring = malloc(MAP_WIDTH*MAP_HEIGHT*3);
    for (int i=0; i<MAP_WIDTH*MAP_HEIGHT*3; i++) {
        *(m->mapstring+i) = '0';
    }
    printf("mapstring created as empty. it is length %lu and is:\n <%s>\n",strlen(m->mapstring),m->mapstring);
    /*m->mapstring =  "00b00b00b00b00b00b00b00b00b00b00b00b00b00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00a00a00a00a00a00a00a00a00a00a00a00a00b00b00b00b00b00b00b00b00b00b00b00b00b00b00b";*/
    //printf("strlen of mapstring %lu\n",strlen(m->mapstring));
    m->renderer = r;
    printf("map section: %d\n",computeMapDataSection(*(yourPlayer->absX),*(yourPlayer->absY)));
    m->loadedTileCount = malloc(sizeof(int));

    SDL_Surface* otherPlrSurf = IMG_Load("data/assets/map/00p.png");
    m->otherPlayer = SDL_CreateTextureFromSurface(r,otherPlrSurf);
    SDL_FreeSurface(otherPlrSurf);

    for (int i=0; i<MAP_WIDTH*MAP_HEIGHT; i++) {
        m->tileCache[i] = newLoadedTile();
        initLoadedTile(m->tileCache[i],r);
    }
    *(m->loadedTileCount) = 1;
    /*for (int i=0; i<MAP_WIDTH; i++) {
        for  (int j=0; j<MAP_HEIGHT; j++) {
            loadTile(m,"00a",i,j);
        }
    }*/
    m->globalPlayerUpdateRequired=malloc(sizeof(int));
    *(m->globalPlayerUpdateRequired)=0;
    for (int i=0; i<MAP_WIDTH; i++) {
        for (int j=0; j<MAP_HEIGHT; j++) {
            m->rendPlayers[i][j]=malloc(sizeof(int));
            *(m->rendPlayers[i][j])=-1;
        }
    }
    printf("map init'd\n");
}

void updateMapString(Map* m, char* changeTo) {
    strcpy(m->mapstring,changeTo);
}

void clearRenderMapData(Map* m) {
    for (int i=0; i<MAP_WIDTH; i++) {
        for (int j=0; j<MAP_HEIGHT; j++) {
            *(m->rendPlayers[i][j])=-1;
        }
    }
}


void renderMap(Map* m, Player* p) {
    //pthread_mutex_lock(&guiLock);
    if (m==NULL)
        return;
    int x = *(p->absX);
    int y = *(p->absY);
    int scrX = x/TILE_SIZE;
    int scrY = y/TILE_SIZE;
    int offX = x%TILE_SIZE;
    int offY = y%TILE_SIZE;
    char curTile[4];
    int c = 0;
    for (int i=0; i<MAP_HEIGHT; i++) {
        for (int j=0; j<MAP_WIDTH; j++) {
            SDL_Rect rendAt = {j*TILE_SIZE,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};
            curTile[0] = *(m->mapstring+c);
            curTile[1] = *(m->mapstring+c+1);
            curTile[2] = *(m->mapstring+c+2);
            curTile[3] = '\0';
            c=c+3;

            //printf("curtile:%s\n",curTile);
            int index = loadTile(m,curTile);

            /*SDL_Surface* tileSurface = IMG_Load("gfx/assets/map/00a.png");
            m->tileTexture[i][j] = SDL_CreateTextureFromSurface(m->renderer,tileSurface);
            SDL_FreeSurface(tileSurface);*/
            SDL_RenderCopy(m->renderer,m->tileCache[index]->tileTexture,NULL,&rendAt);

            if (*(m->rendPlayers[j][i])>-1) {
                /*curTile[0] = '0';
                curTile[1] = '0';
                curTile[2] = 'p';
                curTile[3] = '\0';*/
                SDL_RenderCopy(m->renderer,m->otherPlayer,NULL,&rendAt);
            }
            //SDL_DestroyTexture(m->tileTexture[i][j]);
        }
    }
    renderPlayer(p);
    //pthread_mutex_unlock(&guiLock);

}


void setTile(Map* m, int x, int y, char* changeTo) {
    printf("trying to change to %s\n",changeTo);
    int offset = 3*y*MAP_WIDTH+3*x;
    *(m->mapstring+offset) = *(changeTo);
    *(m->mapstring+offset+1) = *(changeTo+1);
    *(m->mapstring+offset+2) = *(changeTo+2);
    strcpy(yourSettings->tempMapString,m->mapstring);
}

void getBase36(char* fill, int num) {
    char ans[3];
    int a = num;
    while (a>0) {
        int slot = 0;
        int next = a/36;
        while (next>0) {
            next = next/36;
            slot++;
        }
        int add = a/(pow(36,slot));
        ans[slot]=add;

    }
    //a is 97
    //z is 122

    //46655
}

#include "EntityManager.h"
#include <stdlib.h>

EntityManager* newEntityManager() {
    return (EntityManager*)malloc(sizeof(EntityManager));
}

void initEntities(EntityManager* e) {
    e->nextNPCId=malloc(sizeof(int));
    *(e->nextNPCId)=0;
    for (int i=0; i<NUM_NPCS; i++) {
        e->npcs[i]=NULL;
    }
}

void renderEntities(EntityManager* e, SDL_Renderer* r) {
    for (int i=0; i<*(e->nextNPCId); i++) {
        renderNPC(e->npcs[i],r);
    }
}

int createNPC(EntityManager* e, int id, int x, int y, int z, char* name) {
    int nextID = *(e->nextNPCId);
    e->npcs[nextID]=newNPC();
    initNPC(e->npcs[nextID],id,name);
    setNPCCoords(e->npcs[nextID],x,y,z);
    setNPCMemoryID(e->npcs[nextID],nextID);
    *(e->nextNPCId) = nextID+1;
    return nextID;
}

void eraseScreenNPCs(EntityManager* e) {
    for (int i=0; i<*(e->nextNPCId); i++) {
        setNPCVisibility(e->npcs[i],0);
    }
}

void deleteScreenNPCs(EntityManager* e) {
    for (int i=0; i<*(e->nextNPCId); i++) {
        if (e->npcs[i]!=NULL) {
            deleteNPC(e->npcs[i]);
            free(e->npcs[i]);
            e->npcs[i]=NULL;
        }
    }
    *(e->nextNPCId)=0;
}

void processEntityClicks(EntityManager* e, int clickX, int clickY) {
    for (int i=0; i<*(e->nextNPCId);i++) {
        if (e->npcs[i]!=NULL) {
            if (*(e->npcs[i]->visible))
                clickNPC(e->npcs[i],clickX,clickY);
        }
    }
}

NPC* getNPC(EntityManager* e, int datid) {
    if (datid>=*(e->nextNPCId))
        return NULL;
    return e->npcs[datid];
}

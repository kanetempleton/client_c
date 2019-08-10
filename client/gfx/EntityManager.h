#ifndef H_ENTITYMANAGER
#define H_ENTITYMANAGER
#include "state/game/entity/NPC.h"
#define NUM_NPCS 1000

typedef struct {
    NPC* npcs[NUM_NPCS];
    int* nextNPCId;
} EntityManager;

EntityManager* newEntityManager();
void initEntities(EntityManager* e);
void renderEntities(EntityManager* e, SDL_Renderer* r);

//npc methods
int createNPC(EntityManager* e, int id, int x, int y, int z, char* name);
void eraseScreenNPCs(EntityManager* e);
void deleteScreenNPCs(EntityManager* e);

void processEntityClicks(EntityManager* e, int clickX, int clickY);

NPC* getNPC(EntityManager* e, int id);
#endif

#include "Pair.h"
#include <stdlib.h>

Pair* newPair() {
    return (Pair*)malloc(sizeof(Pair));
}

void initPair(Pair* p, int x, int y) {
    p->x0 = malloc(sizeof(int));
    p->x1 = malloc(sizeof(int));
    *(p->x0)=x;
    *(p->x1)=y;
}

void deletePair(Pair* p) {
    free(p->x0);
    free(p->x1);
}

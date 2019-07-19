#ifndef H_PAIR
#define H_PAIR
typedef struct {
    int* x0;
    int* x1;
} Pair;
Pair* newPair();
void initPair(Pair* p, int x, int y);
void deletePair(Pair* p);
#endif

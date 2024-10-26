#ifndef PRO_H
#define PRO_H

#include "common.h"

struct SPU {
    int ip;
    int* RAM;
    int* reg;
    int* code;
};

void Run (stack_t* stk, stack_t* stk_func, SPU *spu);
int* GetArg (SPU *spu);
void Paint (int* data, int x, int y);

#endif

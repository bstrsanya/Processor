#ifndef PRO_H
#define PRO_H

#include "common.h"
#include "stack.h"

struct SPU {
    int ip;
    int* RAM;
    int* reg;
    int* code;
};

enum ERRORS
{
    DIV_ZERO = 1,
    RUN_OK  = 2,
    SNT_ERR = 3
    
};

int Run (stack_t* stk, stack_t* stk_func, SPU* spu);
int* GetArg (int* reg, int* RAM, int* code, int* ip);
void Paint (int* data, int x, int y);
SPU* CpuCtor (int* code);
void CpuDtor (SPU* spu);
int JumpOrNo (int jump, stack_t* stk);

#endif

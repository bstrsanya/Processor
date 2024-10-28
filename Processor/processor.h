#ifndef PRO_H
#define PRO_H

#include "common.h"
#include "stack.h"

struct SPU {
    int ip;
    double* RAM;
    double* reg;
    int* code;
};

enum ERRORS
{
    DIV_ZERO = 1,
    RUN_OK  = 2,
    SNT_ERR = 3
    
};

int Run (stack_t* stk, stack_t* stk_func, SPU* spu);
double* GetArg (double* reg, double* RAM, int* code, int* ip);
void Paint (double* data, int x, int y);
SPU* CpuCtor (int* code);
void CpuDtor (SPU* spu);
int JumpOrNo (int jump, stack_t* stk);

#endif

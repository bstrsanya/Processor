#ifndef PRO_H
#define PRO_H

#include "common.h"
#include "stack.h"
#include "errors.h"

struct SPU {
    int ip;
    double* RAM;
    double* reg;
    int* code;
};

int const  RUN_OK            = 1;
int const argc_for_processor = 2;

int Run (stack_t* stk, stack_t* stk_func, SPU* spu);
double* GetArg (double* reg, double* RAM, int* code, int* ip);
void Paint (double* data, int x, int y);
SPU* CpuCtor (int* code);
void CpuDtor (SPU* spu);

#endif

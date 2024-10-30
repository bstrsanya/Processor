#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "processor.h"

#define DEF_CMD(name, num, code) \
    case name: code break;

int Run (stack_t* stk, stack_t* stk_func, SPU* spu)
{
    int isEnd = true;
    while (isEnd)
    {
        int cmd = spu->code[(spu->ip)++];
        switch (cmd) {

            #include "commands.h"      

            default: {
                printf ("Syntax error: [%d]\n", cmd);
                return SNT_ERR; }
                break; 
        }
    }
    return RUN_OK;
}

double* GetArg (double* reg, double* RAM, int* code, int* ip)
{
    int argType = code[(*ip)++];
    double* ptr = reg;

    if (argType & MASK_CON)
        *ptr = code[ (*ip)++ ] / PRECISION;

    if (argType & MASK_REG)
    {
        if (CompareDouble(*ptr, 0))
            {ptr = &(reg[ (code[(*ip)++]) ]); }
        else
            *ptr += reg[ (code[(*ip)++]) ];
    }

    if (argType & MASK_MEM)
        ptr = & ( RAM[(int) *ptr] );

    return ptr;
}

void Paint (double* data, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (CompareDouble (data[y*i+j], 0))
                printf ("%3c", '.');
            else
                printf ("%3c", '0');
        }
    putchar ('\n');
    }
}

SPU* CpuCtor (int* code)
{
    double* reg_massive = (double*) calloc (NUM_REG, sizeof (double));
    if (reg_massive == NULL) return NULL;

    double* op_mem = (double*) calloc (LEN_RAM, sizeof (double));
    if (op_mem == NULL) return NULL;

    SPU* spu = (SPU*) calloc (1, sizeof (SPU));
    if (spu == NULL) return NULL;

    spu->code = code;
    spu->ip = 0;
    spu->RAM = op_mem;
    spu->reg = reg_massive;

    return spu;
}

void CpuDtor (SPU* spu)
{
    free (spu->RAM); spu->RAM = NULL;
    free (spu->reg); spu->reg = NULL;
    free (spu->code); spu->code = NULL;
    free (spu); spu = NULL;
}
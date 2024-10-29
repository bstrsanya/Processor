#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "processor.h"

//#define Jump(spu) {spu->ip = spu->code[(spu->ip)]}

int Run (stack_t* stk, stack_t* stk_func, SPU* spu)
{
    int isEnd = true;
    while (isEnd)
    {
        int cmd = spu->code[(spu->ip)++];
        switch (cmd) {

            case HLT: {
                isEnd = false; }
                break; 

            case PUSH: {
                double* arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                StackPush (stk, *(arg));
                spu->reg[0] = 0; }
                break; 

            case POP: {
                double a = 0; 
                StackPop (stk, &a);
                double *arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                *arg = a; }
                break;

            case OUTC: {
                double a = 0; 
                StackPop (stk, &a);
                printf ("%c\n", (int) a); }  
                break;           

            case IN: {
                double a = 0;
                scanf ("%lf", &a);
                StackPush (stk, a); }
                break; 

            case SQRT: {
                double a = 0;
                StackPop (stk, &a);
                a = sqrt (a);
                StackPush (stk, a); }
                break; 

            case SUB: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                StackPush (stk, b - a); }
                break; 

            case ADD: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                StackPush (stk, a + b); }
                break; 

            case DIV: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (CompareDouble (a, 0)) 
                {
                    printf ("DIV ON ZERO\n"); 
                    return DIV_ZERO;
                } 
                else StackPush (stk, b / a); }
                break; 

            case OUT: {
                double a = 0; 
                StackPop (stk, &a);
                printf ("%.3lf\n", a); }
                break; 

            case MUL: {
                double a = 0;
                StackPop (stk, &a);
                double b = 0;
                StackPop (stk, &b);
                StackPush (stk, (int) b * a); }
                break; 

            case JB: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0;
                StackPop (stk, &b);
                if (b < a) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JA: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (b > a) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JAE: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (b >= a) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JBE: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (b <= a) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JE: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (CompareDouble (a, b)) 
                     (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JNE: {
                double a = 0; 
                StackPop (stk, &a);
                double b = 0; 
                StackPop (stk, &b);
                if (!CompareDouble (a, b)) 
                    (spu->ip) = spu->code[(spu->ip)];
                else 
                    (spu->ip)++; }
                break; 

            case JMP: {
                int new_pointer = spu->code[(spu->ip)];
                (spu->ip) = new_pointer; }
                break; 

            case RET: {
                double a = 0;
                StackPop (stk_func, &a);
                spu->ip = (int) a; }
                break; 

            case CALL: {
                StackPush (stk_func, spu->ip + 1);
                spu->ip = spu->code[spu->ip]; }
                break; 

            case DRAW: {
                Paint (spu->RAM, SQUARE, SQUARE); }
                break; 

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
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "processor.h"


int Run (stack_t* stk, stack_t* stk_func, SPU* spu)
{
    int isEnd = 1;
    while (isEnd)
    {
        int cmd = spu->code[(spu->ip)++];
        switch (cmd) {

            case HLT: {
                isEnd = 0; }
                break; 

            case PUSH: {
                int* arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                StackPush (stk, *arg);
                spu->reg[0] = 0; }
                break; 

            case POP: {
                int a = 0; StackPop (stk, &a);
                int *arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                *arg = a; }
                break;

            case OUTC: {
                int a = 0; StackPop (stk, &a);
                printf ("%c\n", a); }  
                break;           

            case IN: {
                int a = 0;
                scanf ("%d", &a);
                StackPush (stk, a); }
                break; 

            case SQRT: {
                int a = 0;
                StackPop (stk, &a);
                a = (int) sqrt (a);
                StackPush (stk, a); }
                break; 

            case SUB: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, b - a); }
                break; 

            case ADD: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, a + b); }
                break; 

            case DIV: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (a == 0) 
                {
                    printf ("DIV ON ZERO\n"); 
                    return DIV_ZERO;
                } 
                else StackPush (stk, (int) b / a); }
                break; 

            case OUT: {
                int a = 0; StackPop (stk, &a);
                printf ("%d\n", a); }
                break; 

            case MUL: {
                int a = 0;
                StackPop (stk, &a);
                int b = 0;
                StackPop (stk, &b);
                StackPush (stk, (int) b * a); }
                break; 

            case JB:
            case JA:
            case JBE:
            case JAE:
            case JE:
            case JNE:
            case JMP: {
                if (JumpOrNo (spu->code[spu->ip-1], stk))
                {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; 
                }
                else (spu->ip)++; }
                break; 

            case RET: {
                int a = 0;
                StackPop (stk_func, &a);
                spu->ip = a; }
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

int* GetArg (int* reg, int* RAM, int* code, int* ip)
{
    int argType = code[(*ip)++];
    int* ptr = reg;

    if (argType & MASK_CON)
        *ptr = code[ (*ip)++ ];

    if (argType & MASK_REG)
    {
        if (*ptr == 0)
            {ptr = &(reg[ (code[(*ip)++]) ]); }
        else
            *ptr += reg[ (code[(*ip)++]) ];
    }

    if (argType & MASK_MEM)
        ptr = & ( RAM[*ptr] );

    return ptr;
}

void Paint (int* data, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (data[y*i+j] == 0)
                printf ("%3c", '.');
            else
                printf ("%3c", '0');
        }
    putchar ('\n');
    }
}

SPU* CpuCtor (int* code)
{
    int* reg_massive = (int*) calloc (NUM_REG, sizeof (int));
    int* op_mem = (int*) calloc (LEN_RAM, sizeof (int));
    SPU* spu = (SPU*) calloc (1, sizeof (SPU));

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

int JumpOrNo (int jump, stack_t* stk)
{
    if (jump == JMP)
        return 1;
    else 
    {
        int a = 0; 
        int b = 0;
        StackPop (stk, &a);
        StackPop (stk, &b);

        switch (jump)
        {
            case JA:
                if (b > a) return 1;
                break;

            case JAE:
                if (b >= a) return 1;
                break;

            case JB:
                if (b < a) return 1;
                break;

            case JBE:
                if (b <= a) return 1;
                break;
                
            case JE:
                if (b == a) return 1;
                break;

            case JNE: 
                if (b != a) return 1;
                break;

            default: 
                return 0;
        }
    }
    return 0;
}
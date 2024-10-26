#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "processor.h"

void Run (stack_t* stk, stack_t* stk_func, SPU* spu)
{
    int isEnd = 1;
    while (isEnd)
    {
        int cmd = spu->code[(spu->ip)++];
        switch (cmd) {

            case HLT: {
                isEnd = 0;
                break; }

            case PUSH: {
                int* arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                StackPush (stk, *arg);
                spu->reg[0] = 0;
                break; }

            case POP:
            {
                int a = 0; StackPop (stk, &a);
                int *arg = GetArg (spu->reg, spu->RAM, spu->code, &(spu->ip));
                *arg = a;
                break;
            }

            case PUTC:
            {
                int a = 0; StackPop (stk, &a);
                printf ("%c\n", a);    
                break;           
            }

            case IN: {
                int a = 0;
                scanf ("%d", &a);
                StackPush (stk, a);
                break; }

            case SQRT: {
                int a = 0;
                StackPop (stk, &a);
                a = (int) sqrt (a);
                StackPush (stk, a);
                break; }

            case SUB: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, b - a);
                break; }

            case ADD: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, a + b);
                break; }

            case DIV: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (a == 0) printf ("DIV ON ZERO\n"); // TODO assert -> return 
                else StackPush (stk, (int) b / a); 
                break; }

            case OUT: {
                int a = 0; StackPop (stk, &a);
                printf ("%d\n", a);
                break; }
//OUTC %c
// PUSH 67 PUSH 10 PUSH 43 outc outc outc -> "C +"

            case MUL: {
                int a = 0;
                StackPop (stk, &a);
                int b = 0;
                StackPop (stk, &b);
                StackPush (stk, (int) b * a);
                break; }

            case JB: {
                int a = 0; //TODO use define for jmp
                StackPop (stk, &a);
                int b = 0;
                StackPop (stk, &b);
                if (b < a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case JA: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b > a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case JAE: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b >= a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case JBE: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b <= a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case JE: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b == a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case JNE: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b != a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++; }
                break;

            case JMP:  {
                int new_pointer = spu->code[(spu->ip)];
                (spu->ip) = new_pointer;
                break; }

            case RET: {
                int a = 0;
                StackPop (stk_func, &a);
                spu->ip = a;
                break; }

            case CALL: {
                StackPush (stk_func, spu->ip + 1);
                spu->ip = spu->code[spu->ip];
                break; }

            case DRAW: {
                Paint (spu->RAM, SQUARE, SQUARE);
                break; }

            default: {
                printf ("Syntax error: [%d]\n", cmd);
                isEnd = 0;
                break; }
        }
    }
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
    int* reg_massive = (int*) calloc (LEN_REG, sizeof (int));
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
#include <stdio.h>
#include <math.h>

#include "processor.h"

void Run (stack_t *stk, stack_t *stk_func, SPU *spu)
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
                int* arg = GetArg (spu);
                StackPush (stk, *arg);
                spu->reg[0] = 0;
                break; }

            case POP:
            {
                int a = 0; StackPop (stk, &a);
                int *arg = GetArg (spu);
                *arg = a;
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
                StackPush (stk, (int) b / a); //TODO check a - is 0
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
                Paint (spu->RAM, square, square);
                break; }

            default: {
                printf ("Syntax error: '%d'\n", cmd);
                break; }
        }
    }
}

int* GetArg (SPU *spu)
{
    int argType = spu->code[(spu->ip)++];
    int* ptr = spu->reg;

    if (argType & MASK_CON)
        *ptr = spu->code[ (spu->ip)++ ];

    if (argType & MASK_REG)
    {
        if (*ptr == 0)
            {ptr = &(spu->reg[ (spu->code[(spu->ip)++]) ]); }
        else
            *ptr += spu->reg[ (spu->code[(spu->ip)++]) ];
    }

    if (argType & MASK_MEM)
        ptr = & ( spu->RAM[*ptr] );

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
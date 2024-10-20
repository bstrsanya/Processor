#include <stdio.h>

#include "processor.h"

void Run (FILE* file, stack_t *stk, SPU *spu)
{
    while (1)
    {

        int cmd = spu->code[(spu->ip)++];

        if (cmd == HLT) break;

        switch (cmd) {

            case PUSH: {
                int* arg = GetArg (spu);
                StackPush (stk, *arg);
                spu->reg[0] = 0;
                break; }

            case POP: {
                int a = 0; StackPop (stk, &a);
                int *arg = GetArg (spu);
                *arg = a;
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
                StackPush (stk, (int) b / a);
                break; }
            
            case OUT: {
                int a = 0; StackPop (stk, &a);
                printf ("res = %d\n", a);
                break; }
        
            case MUL: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, (int) b * a);
                break; }

            case JB: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
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
                else (spu->ip)++;
                break; }

            case JMP: {
                int new_pointer = spu->code[(spu->ip)];
                (spu->ip) = new_pointer;
                break; }

            default: {
                printf ("Syntax error: '%s'\n", cmd);
                break; }
        }
    }
}

int* GetArg (SPU *spu)
{
    int argType = spu->code[(spu->ip)++];
    int* ptr = spu->reg;
    int arg_reg = 0;
    int argValue = 0;

    if (argType & 1) 
    {
        *ptr = spu->code[ (spu->ip)++ ];
    }

    if (argType & 2) 
    {
        ptr = & ( spu->reg[ (spu->code[(spu->ip)++]) ] );
        arg_reg = *ptr; // значение CX
        *ptr += spu->reg[0];
    }
    
    if (argType & 4) 
    {
        ptr = & ( spu->RAM[arg_reg + spu->reg[0]] );
    }
      
    return ptr;
}
#include <stdio.h>

#include "processor.h"

void Run (FILE* file, stack_t *stk, SPU *spu)
{
    while (1)
    {
        //DumpMassive (spu->reg, 5);
        int cmd = spu->code[(spu->ip)++];

        if (cmd == hlt) break;

        switch (cmd) {

            case push: {
                int arg = spu->code[(spu->ip)++];
                StackPush (stk, arg);
                break; }

            case sub: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, b - a);
                break; }
  
            case add: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, a + b);
                break; }

            case DIV: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, (int) b / a);
                break; }
            
            case out: {
                int a = 0; StackPop (stk, &a);
                printf ("res = %d\n", a);
                break; }
        
            case mul: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                StackPush (stk, (int) b * a);
                break; }
            
            case pop: {
                int a = 0; StackPop (stk, &a);
                spu->reg[spu->code[(spu->ip)++]] = a;
                break; }

            case jb: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b < a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case ja: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b > a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case jae: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b >= a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case jbe: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b <= a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }
            
            case je: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b == a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case jne: {
                int a = 0; StackPop (stk, &a);
                int b = 0; StackPop (stk, &b);
                if (b != a) {
                    int new_pointer = spu->code[(spu->ip)];
                    (spu->ip) = new_pointer; }
                else (spu->ip)++;
                break; }

            case jmp: {
                int new_pointer = spu->code[(spu->ip)];
                (spu->ip) = new_pointer;
                break; }

            default: {
                printf ("Syntax error: '%s'\n", cmd);
                break; }
        }
    }
}
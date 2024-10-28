#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "processor.h"

int main(int argc, const char *argv[]) 
{
    if (argc != 2) 
    {
        printf ("Incorrect number of arguments\n");
        return 1;
    }

    int* code = MyFread (argv[1], "rb"); // first argument command line
    
    stack_t stk = {};
    StackCtor (&stk, SIZE_STACK);

    stack_t stk_func = {};
    StackCtor (&stk_func, SIZE_STACK);

    SPU* spu = CpuCtor (code);
    
    Run (&stk, &stk_func, spu);

    CpuDtor (spu);
    FreeStack (&stk);
    FreeStack (&stk_func);

    return 0;
}
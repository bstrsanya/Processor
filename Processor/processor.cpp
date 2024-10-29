#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "processor.h"

#define CHECK(arg, value, file, line) if (arg == value) {printf ("Errors %s:%d\n", file, line); return ERROR;}

int main(int argc, const char *argv[]) 
{
    if (argc != argc_for_processor) 
    {
        printf ("Incorrect number of arguments\n");
        return ERROR;
    }

    int* code = MyFread (argv[1], "rb", LEN_CODE); // first argument command line
    CHECK (code, NULL, __FILE__, __LINE__);
    
    stack_t stk = {};
    StackCtor (&stk, SIZE_STACK);

    stack_t stk_func = {};
    StackCtor (&stk_func, SIZE_STACK);

    SPU* spu = CpuCtor (code);
    CHECK (spu, NULL, __FILE__, __LINE__);
    
    Run (&stk, &stk_func, spu);

    CpuDtor (spu);
    FreeStack (&stk);
    FreeStack (&stk_func);

    return 0;
}
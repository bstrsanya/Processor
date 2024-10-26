#include <stdio.h>
#include <strings.h>

#include "processor.h"

int main(int argc, const char *argv[]) 
{
    if (argc != 2) printf ("More arg\n");
    int code[len_code]; //TODO chcek argc
    MyFread (argv[1], "rb", code); //TODO не называй это своим fread //TODO const num of file input - not use this naming

    stack_t stk = {};
    StackCtor (&stk, size_stack);

    stack_t stk_func = {};
    StackCtor (&stk_func, 100);

    int reg_massive[len_reg] = {};
    int op_mem[len_ram] = {};
    SPU spu = {.ip = 0, .RAM = op_mem, .reg = reg_massive, .code = code};

    Run (&stk, &stk_func, &spu);
    //TODO return 0;
}






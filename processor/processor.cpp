#include <stdio.h>
#include <strings.h>

#include "processor.h"

int main() 
{
    FILE *file = fopen ("program_code.bin", "rb");
    if (file == NULL) printf ("Erorrs open file\n");

    int code[len_code] = {};
    fread (code, sizeof (code[0]), sizeof (code) / sizeof (code[0]), file);
    fclose (file);

    stack_t stk = {};
    StackCtor (&stk, 10);

    int ip = 0;
    register int reg_massive[5] = {};
    int op_mem[100] = {};
    SPU spu = {.ip = 0, .RAM = op_mem, .reg = reg_massive, .code = code};

    Run (&stk, &spu);

    //DumpMassive (spu.reg, 5);
    //DumpMassive (spu.RAM, 10);
    //Paint (spu.RAM, 9, 9);    
}



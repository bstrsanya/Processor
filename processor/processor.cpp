#include <stdio.h>
#include <strings.h>

#include "processor.h"

int main() 
{
    FILE *file = fopen ("program_code.bin", "rb");
    if (file == NULL) printf ("Erorrs open file\n");

    int code[100] = {};
    fread (code, sizeof (code[0]), sizeof (code) / sizeof (code[0]), file);

    stack_t stk = {};
    StackCtor (&stk, 10);

    int ip = 0;
    register int reg_massive[5] = {};
    int op_mem[100] = {};
    SPU spu = {.ip = 0, .RAM = op_mem, .reg = reg_massive, .code = code};


    
    Run (file, &stk, &spu);
    
    fclose (file);
}



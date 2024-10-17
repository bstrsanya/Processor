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
    
    Run (file, &stk, code);
    
    fclose (file);
}



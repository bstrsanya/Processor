#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"

int main(int argc, const char *argv[])
{
    if (argc != 3) printf ("Incorrect number of arguments\n");
    FILE *file_input  = MyFopen (argv[1], "rb");  // first argument command line
    FILE *file_output = MyFopen (argv[2], "wb");  // second argument command line

    str_asm* asm_data = AsmCtor (file_input);

    DoubleCompilation (asm_data);

    fwrite (asm_data->code, sizeof (asm_data->code[0]), (size_t) asm_data->ip, file_output);
    fclose (file_input);
    fclose (file_output);

    AsmDtor (asm_data);
}


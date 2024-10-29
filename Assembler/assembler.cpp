#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"

#define CHECK(arg, value, file, line) if (arg == value) {printf ("Errors %s:%d\n", file, line); return ERROR;}

int main(int argc, const char *argv[])
{
    if (argc != argc_for_assembler)
    {
        printf ("Incorrect number of arguments\n");
        return ERROR;
    }

    str_asm* asm_data = AsmCtor (argv[1]);          // first argument command line
    CHECK (asm_data, NULL,  __FILE__, __LINE__);

    int code_err = DoubleCompilation (asm_data);
    if (code_err != COMPL_OK) 
    {
        printf ("ERROR NUMBER: %d\n", code_err);
        return code_err;
    }

    int write_file = WriteFile (asm_data, argv[2]); // second argument command line
    CHECK (write_file, ERROR, __FILE__, __LINE__);

    AsmDtor (asm_data);
    return 0;
}


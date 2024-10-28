#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf ("Incorrect number of arguments\n");
        return 1;
    }

    FILE *file_input  = fopen (argv[1], "rb");  // first argument command line
    FILE *file_output = fopen (argv[2], "wb");  // second argument command line

    if (file_input == NULL or file_output == NULL) 
    {
        printf ("The file could not be opened");
        return 1;
    }

    size_t size = 0;
    char* massive = ReadFile (file_input, &size);
    char s1[30] = "";
    int d1 = 0;
    sscanf (massive, "%s%n", s1, &d1);
    printf ("%s = %d", s1, d1);

    //str_asm* asm_data = AsmCtor (file_input);

    //int code_err = DoubleCompilation (asm_data);
    // if (code_err != COMPL_OK) 
    // {
    //     printf ("ERROR NUMBER: %d\n", code_err);
    //     return code_err;
    // }

    // fwrite (asm_data->code, sizeof (asm_data->code[0]), (size_t) asm_data->ip, file_output);

    fclose (file_input);
    fclose (file_output);

    // AsmDtor (asm_data);
    return 0;
}


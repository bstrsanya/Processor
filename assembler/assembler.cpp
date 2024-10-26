#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"

int main(int argc, const char *argv[])
{
    if (argc != 3) printf ("More arg\n");
    FILE *file_input  = MyFopen (argv[1], "rb");
    FILE *file_output = MyFopen (argv[2], "wb");

    STR_labels labels[len_labels] = {};
    int arr_code[len_code] = {};
    str_asm asm_data = {.code = arr_code, .labels = labels, .file_input = file_input, .ip = 0};
    DoubleCompilation (&asm_data);

    fwrite (asm_data.code, sizeof (asm_data.code[0]), (size_t) asm_data.ip, file_output);

    fclose (file_input);
    fclose (file_output);

    AsmDtor (&asm_data);
}


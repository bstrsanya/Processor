#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"
#include "processor.h"

int main()
{
    //Fopen чтобы проверка была автоматом возвращать указатель
    // динамическая память
    FILE *file_input = fopen ("program.asm", "rb");
    FILE *file_output = fopen ("program_code.bin", "wb");

    if (file_input == NULL) printf ("Erorrs open file_input\n");
    if (file_output == NULL) printf ("Erorrs open file_output\n");

    STR_labels labels[len_labels] = {};
    int code[100] = {};
    
    Read_Asm (code, labels, file_input);
    //DumpMassive (code, 20);
    //printf ("%s - %d\n", labels[0].name_mark, labels[0].ptr_mark);
    if (fseek (file_input, 0, SEEK_SET)) printf ("error fssek\n");
    Read_Asm (code, labels, file_input);
    //DumpMassive (code, 20);
    //printf ("%s - %d\n", labels[0].name_mark, labels[0].ptr_mark);
    

    fwrite (code, sizeof (code[0]), sizeof (code) / sizeof (code[0]), file_output);
    
    fclose (file_input);
    fclose (file_output);
}


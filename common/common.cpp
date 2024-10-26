#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "common.h"

FILE* MyFopen (const char* name, const char* mode) //TODO assert
{
    assert(name);

    FILE* fname = fopen (name, mode);
    if (fname == NULL) 
    {
        printf ("Error open file: %s\n", name);
        assert (0); //TODO not use assert in this place
    }
    return fname;
}

void DumpMassive (int* data, int size)
{
    for (int i = 0; i < size; i++)
        printf ("%4d", i);

    putchar ('\n');

    for (int j = 0; j < size; j++)
        printf ("%4d", data[j]);

    putchar ('\n');
}

int* MyFread(const char* name, const char* mode)
{
    FILE *file = MyFopen (name, mode);
    int* code = (int*) calloc (LEN_CODE, sizeof (int));
    fread (code, sizeof (int), LEN_CODE, file);
    fclose (file);
    return code;
}



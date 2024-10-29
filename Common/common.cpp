#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common.h"

void DumpMassive (int* data, int size)
{
    for (int i = 0; i < size; i++)
        printf ("%4d", i);

    putchar ('\n');

    for (int j = 0; j < size; j++)
        printf ("%4d", data[j]);

    putchar ('\n');
}

int* MyFread(const char* name, const char* mode, int size)
{
    FILE *file = fopen (name, mode);
    if (file == NULL) return NULL;

    int* code = (int*) calloc ((size_t) size, sizeof (int));
    if (code == NULL) return NULL;

    fread (code, sizeof (int), size_t (size), file);
    fclose (file);
    return code;
}

int CompareDouble (double argument_1, double argument_2)
{
    if (fabs (argument_1 - argument_2) < SMALL)
        return true;
         
    return false;
}


#include <stdio.h>
#include "processor.h"

void DumpMassive (int* data, int size)
{
    for (int i = 0; i < size; i++)
        printf ("%4d", i);

    putchar ('\n');

    for (int j = 0; j < size; j++)
        printf ("%4d", data[j]);

    putchar ('\n');

}

void Paint (int* data, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
            printf ("%3d", data[y*i+j]);
    putchar ('\n');
    }
}

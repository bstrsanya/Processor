#ifndef COMMON_H
#define COMMON_H

void DumpMassive (int* data, int size);
int* MyFread(const char* name, const char* mode, int size);
int CompareDouble (double argument_1, double argument_2);

#define DEF_CMD(name, num, code) name = num,


enum COMMAND
{
    #include "commands.h"
};

#undef DEF_CMD

enum MASK
{
    MASK_MEM  = 0b0000'0100,
    MASK_REG  = 0b0000'0010,
    MASK_IMC  = 0b0000'0001
};

const int PRECISION   = 3;
const int LEN_COMMAND = 30;
const int LEN_LABELS  = 20;
const int LEN_RAM     = 1225;
const int NUM_REG     = 5;
const int SIZE_STACK  = 10;
const int SQUARE      = 35;
const int LEN_CODE    = 1000;
const double SMALL    = 10e-8;

struct STR_labels {
    char name_label[LEN_COMMAND] = "";
    int  ptr_label = -1;    // место свободно, если метка стоит на -1, если не определена но занята err
};

#endif

#ifndef PRO_H
#define PRO_H

#include "stack.h"



enum command 
{ //капсом сделать
    AX    = 1,
    BX    = 2,
    CX    = 3,
    DX    = 4,

    push  = 101,
    sub   = 102,
    add   = 103,
    DIV   = 104,
    out   = 105,
    mul   = 106,
    pop   = 107,
                  // прыжок, если
    jb    = 109,  // <
    ja    = 110,  // >
    jae   = 111,  // >=
    jbe   = 112,  // <=
    je    = 113,  // =
    jne   = 114,  // != 
    jmp   = 115,  // прыжок всегда

    hlt   = -1   

};

const int len_command = 30;
const int len_labels = 20;

struct STR_labels {
    int free = 0;                // если ноль значит свободное место, если 1 значит занято
    char name_mark[len_command] = "";
    int ptr_mark = -1;
}; 

struct SPU {
    int ip;
    int* RAM;
    int* reg;
    int* code;
};

void Run (FILE *file, stack_t *stk, SPU *spu);
void DumpMassive (int* data, int size);

#endif

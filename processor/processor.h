#ifndef PRO_H
#define PRO_H

#include "stack.h"

enum command 
{
    AX    = 1,
    BX    = 2,
    CX    = 3,
    DX    = 4,

    PUSH  = 101,
    SUB   = 102,
    ADD   = 103,
    DIV   = 104,
    OUT   = 105,
    MUL   = 106,
    POP   = 107,
    MARK  = 108,
                  // прыжок, если
    JB    = 109,  // <
    JA    = 110,  // >
    JAE   = 111,  // >=
    JBE   = 112,  // <=
    JE    = 113,  // =
    JNE   = 114,  // != 
    JMP   = 115,  // прыжок всегда
    JUMP  = 116,  // существует какой-то прыжок

    HLT   = -1,
    err   = -2,
    bad_str = -3

};

const int len_command = 30;
const int len_labels = 20;

struct STR_labels {
    int free = 0;                // если ноль значит свободное место, если 1 значит занято
    char name_mark[len_command] = "";
    int  ptr_mark = -1;             // место свободно, если метка стоит на -1
}; 

struct SPU {
    int ip;
    int* RAM;
    int* reg;
    int* code;
};

void Run (FILE *file, stack_t *stk, SPU *spu);
void DumpMassive (int* data, int size);
int* GetArg (SPU *spu);
int* GetArg_for_pop (SPU *spu);

#endif

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
    LABEL  = 108,
                  // прыжок, если
    JB    = 109,  // <
    JA    = 110,  // >
    JAE   = 111,  // >=
    JBE   = 112,  // <=
    JE    = 113,  // =
    JNE   = 114,  // != 
    JMP   = 115,  // прыжок всегда
    JUMP  = 116,  // существует какой-то прыжок
    CALL  = 117,
    RET   = 118,
    IN    = 119,
    SQRT  = 120,

    INF      = 121,
    NOROOTS  = 122,
    ONEROOTS = 123,
    TWOROOTS = 124,

    HLT       = -1,
    err       = -2,
    bad_str   = -3,
    len_code  = 1000,
    MASK_MEM  = 4, 
    MASK_REG  = 2,
    MASK_CON  = 1
};

const int len_command = 30;
const int len_labels  = 20;
const int len_ram     = 20;
const int len_reg     = 5;
const int size_stack  = 10;

struct STR_labels {
    char name_label[len_command] = "";
    int  ptr_label = -1;    // место свободно, если метка стоит на -1, если не определена но занята err
}; 

struct SPU {
    int ip;
    int* RAM;
    int* reg;
    int* code;
};

void Run (stack_t *stk, SPU *spu);
void DumpMassive (int* data, int size);
int* GetArg (SPU *spu);
void Paint (int* data, int x, int y);

#endif

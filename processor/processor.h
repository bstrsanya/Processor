#ifndef PRO_H
#define PRO_H

#include "stack.h"

int reg[5] = {};

enum command 
{
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
    pushr = 108,
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

#endif

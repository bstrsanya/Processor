#ifndef COMMON_H
#define COMMON_H

#include "stack.h"

FILE* MyFopen (const char* name, const char* mode);
void DumpMassive (int* data, int size);
void MyFread(const char* name, const char* mode, int* code);

enum command //TODO is not command
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
    CALL  = 117,
    RET   = 118,
    IN    = 119,
    SQRT  = 120,
    DRAW  = 121,

    HLT       = -1,
    err       = -2,
    bad_str   = -3,
    len_code  = 1000,
    MASK_MEM  = 4, //TODO 0x 0b '0b'
    MASK_REG  = 2,
    MASK_CON  = 1
};

const int len_command = 30;
const int len_labels  = 20;
const int len_ram     = 1225;
const int len_reg     = 5;
const int size_stack  = 10;
const int square      = 35;

struct STR_labels {
    char name_label[len_command] = "";
    int  ptr_label = -1;    // место свободно, если метка стоит на -1, если не определена но занята err
};

#endif

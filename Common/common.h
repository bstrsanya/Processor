#ifndef COMMON_H
#define COMMON_H



FILE* MyFopen (const char* name, const char* mode);
void DumpMassive (int* data, int size);
int* MyFread(const char* name, const char* mode);

enum command
{
    PUSH  = 101,
    SUB   = 102,
    ADD   = 103,
    DIV   = 104,
    OUT   = 105,
    MUL   = 106,
    POP   = 107, 
    OUTC  = 120,
                  // прыжок, если
    JB    = 108,  // <
    JA    = 109,  // >
    JAE   = 110,  // >=
    JBE   = 111,  // <=
    JE    = 112,  // =
    JNE   = 113,  // !=
    JMP   = 114,  // прыжок всегда

    CALL  = 115,
    RET   = 116,
    IN    = 117,
    SQRT  = 118,
    DRAW  = 119,
    HLT   = -1
};

enum MASK
{
    MASK_MEM  = 0b0000'0100,
    MASK_REG  = 0b0000'0010,
    MASK_CON  = 0b0000'0001
};

enum nothing 
{
    LABEL  = 120,
    ERR       = -2,
    WRONG_CMD   = -3
};


const int LEN_COMMAND = 30;
const int LEN_LABELS  = 20;
const int LEN_RAM     = 1225;
const int NUM_REG     = 5;
const int SIZE_STACK  = 10;
const int SQUARE      = 35;
const int LEN_CODE    = 1000;

struct STR_labels {
    char name_label[LEN_COMMAND] = "";
    int  ptr_label = -1;    // место свободно, если метка стоит на -1, если не определена но занята err
};

#endif

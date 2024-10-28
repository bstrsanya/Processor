#ifndef FUNC_H
#define FUNC_H

#include "common.h"
#include "ReadFile.h"
#include "SizeFile.h"

struct str_asm {
    int* code;
    STR_labels* labels;
    char* array_code;
    int ptr;
    int ip;
    int size_file;
};

int ReadAsm (str_asm* asm_data);
int FindLabel (char* arg, int* code, int* ip, struct STR_labels* labels);
int MyAtoi (char* str, int size);
int WorkArg (str_asm* asm_data, char* s2);
int CompilationCommand (int* code, int* ip, char* str);
void PutLabel (STR_labels *labels, int* ip, char* cmd);
int DoubleCompilation (str_asm* asm_data);
str_asm* AsmCtor (FILE* file_input);
void AsmDtor (str_asm* asm_data);
int IsLabel (char* arg);
int CreatMask (char* arg, int* n_push, int* n_reg, int* im_const);
void CreatCode (int* code, int* ip, int n_push, int im_const, int n_reg);

enum ERRORS
{
    WRONG_LABEL = 1,
    RIGHT_LABEL = 2,
    NOT_LABEL   = 3,
    READ_OK     = 4,
    COMPL_OK   = 5,
    WRONG_REG  = 6,
    RIGHT_MASK  = 7,
    WRONG_ARG   = 8,
    ARG_OK     = 9,
    WRONG_STR  = 10,
    NOT_NUMBER = 2147483640    
};
#endif

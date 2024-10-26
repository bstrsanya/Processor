#ifndef FUNC_H
#define FUNC_H

#include "common.h"

struct str_asm {
    int* code;
    STR_labels* labels;
    FILE* file_input;
    int ip;
};

void ReadAsm (str_asm* asm_data);
int FindLabel (FILE* file_input, int* code, int* ip, struct STR_labels* labels);
int MyAtoi (char* str, int size);
void WorkArg (char* arg, int* n_push, int* n_reg, int* im_const, int* code, int* ip);
command CompilationCommand (FILE* file_input, int* code, int* ip, char* str);
void PutLabel (STR_labels *labels, int* ip, char* cmd);
void DoubleCompilation (str_asm* asm_data);
void AsmDtor (str_asm* asm_data);

#endif

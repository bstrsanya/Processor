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
int FindLabel (char* arg, int* code, int* ip, struct STR_labels* labels);
int MyAtoi (char* str, int size);
void WorkArg (FILE* file_input, int* code, int* ip, STR_labels* labels);
int CompilationCommand (int* code, int* ip, char* str);
void PutLabel (STR_labels *labels, int* ip, char* cmd);
void DoubleCompilation (str_asm* asm_data);
str_asm* AsmCtor (FILE* file_input);
void AsmDtor (str_asm* asm_data);

#endif

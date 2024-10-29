#ifndef FUNC_H
#define FUNC_H

#include "common.h"
#include "errors.h"
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

int const LABEL              = 120;
int const argc_for_assembler = 3;
int const EMPTY_LABEL        = -1;

int ReadAsm (str_asm* asm_data);
int FindLabel (char* arg, int* code, int* ip, struct STR_labels* labels);
int MyAtoi (char* str, int size);
int WorkArg (str_asm* asm_data, char* s2);
int CompilationCommand (int* code, int* ip, char* str);
void PutLabel (STR_labels *labels, int* ip, char* cmd);
int DoubleCompilation (str_asm* asm_data);
str_asm* AsmCtor (const char* argv);
void AsmDtor (str_asm* asm_data);
int IsLabel (char* arg);
int CreatMask (char* arg, int* n_push, int* n_reg, int* im_const);
void CreatCode (int* code, int* ip, int n_push, int im_const, int n_reg);
int WriteFile (str_asm* asm_data, const char* argv);


#endif

#ifndef FUNC_H
#define FUNC_H
#include "processor.h"
void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input);
void FindMark (FILE* file_input, int* code, int* ip, struct STR_labels* labels);
int MyAtoi (char* str, int size);
void WorkArg (char* arg, int* n_push, int* n_reg, int* im_const, int* code, int* ip);
command ReadCommand (FILE* file_input, int* code, int* ip);


#endif
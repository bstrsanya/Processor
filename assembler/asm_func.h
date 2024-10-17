#ifndef FUNC_H
#define FUNC_H

void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input);
void FindMark (FILE* file_input, int* code, int* ip, struct STR_labels* labels);

#endif
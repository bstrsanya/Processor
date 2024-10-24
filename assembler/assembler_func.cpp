#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "asm_func.h"
#include "processor.h"

#define CHECK(cmd, arg, code, ip) {if (strcmp (cmd, #arg) == 0) {code[(*ip)++] = arg; return arg;}}

void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input)
{
    stack_t addr_trans = {};
    StackCtor (&addr_trans, size_stack);

    int ip = 0; 
    while (1)
    {
        //DumpMassive (code, 30);
        char cmd[len_command] = "";
        command code_cmd = Compilation_Command (file_input, code, &ip, cmd);

        if (code_cmd == err) break;
        switch (code_cmd) {
        
            case (PUSH): 
            case (POP): {
                char arg[len_command] = "";
                fscanf (file_input, "%s", arg);

                int n_push   = 0;
                int n_reg    = 0;
                int im_const = MyAtoi (arg, strlen (arg));

                WorkArg (arg, &n_push, &n_reg, &im_const, code, &ip);  
                if ((code_cmd == POP) && (n_push == 1))  {printf ("pop %d - illegal operation\n", im_const); assert (0);}
                break; }

            case (LABEL): {
                PutLabel (file_input, labels, &ip, cmd);
                break; }

            case (JB): 
            case (JBE): 
            case (JA): 
            case (JAE): 
            case (JE): 
            case (JNE): 
            case (JMP): {
                if (!Find_Label (file_input, code, &ip, labels)) code[ip++] = -1;
                break; }

            case (CALL): {
                code[ip++] = CALL;
                StackPush (&addr_trans, ip+1);
                if (!Find_Label (file_input, code, &ip, labels)) code[ip++] = -1; 
                break; }

            case (RET): {
                int b = 0; StackPop (&addr_trans, &b);
                code[ip++] = b; 
                break; }

            case (bad_str): {
                printf ("Try again\n");
                assert (0);  }
        }
    }
}

int Find_Label (FILE* file_input, int* code, int* ip, struct STR_labels* labels)
{
    char label[len_command] = "";
    fscanf (file_input, "%s", label);

    if (strchr (label, ':') != NULL)
    {
        label [(int) (strchr (label, ':') - &label[0])] = ' ';
        for (int count = 0; count < len_labels; count++)
            if (strcmp (label, labels[count].name_label) == 0)
            {
                code[(*ip)++] = labels[count].ptr_label;
                return 1;
            }
    }
    else
        {code[(*ip)++] = atoi (label); return 1;}
    return 0;
}

void PutLabel (FILE *file_input, STR_labels *labels, int* ip, char* cmd)
{
    cmd [(strchr (cmd, ':') - &cmd[0])] = ' ';
    for (int count = 0; count < len_labels; count++)
    {
        if (labels[count].ptr_label == -1)
        {
            strcpy (labels[count].name_label, cmd);
            labels[count].ptr_label = *ip;
            break;
        }
    }
}

int MyAtoi (char* str, int size)
{
    for (int i = 0; i < size; i++)
        if (isdigit (str[i])) return atoi (&str[i]);

    return -1;   
}

void WorkArg (char* arg, int* n_push, int* n_reg, int* im_const, int* code, int* ip)
{
    if ((strchr (arg, '[') != NULL) && (strchr (arg, ']') != NULL)) *n_push |= MASK_MEM;

    if (strstr (arg, "AX") != NULL) {*n_push |= MASK_REG; *n_reg = AX;}
    if (strstr (arg, "BX") != NULL) {*n_push |= MASK_REG; *n_reg = BX;}
    if (strstr (arg, "CX") != NULL) {*n_push |= MASK_REG; *n_reg = CX;}
    if (strstr (arg, "DX") != NULL) {*n_push |= MASK_REG; *n_reg = DX;}
    //ax bx 
    //r%cx
    if (*im_const != -1) *n_push |= MASK_CON;
    code[(*ip)++] = *n_push;
    if (*im_const != -1) code[(*ip)++] = *im_const;
    if (*n_reg != 0) code[(*ip)++] = *n_reg; 
}

command Compilation_Command (FILE* file_input, int* code, int* ip, char* cmd)
{
    if (fscanf (file_input, "%s", cmd) == EOF) return err;

    CHECK (cmd, PUSH, code, ip);
    CHECK (cmd, POP,  code, ip);
    CHECK (cmd, SUB,  code, ip);
    CHECK (cmd, ADD,  code, ip);
    CHECK (cmd, DIV,  code, ip);
    CHECK (cmd, OUT,  code, ip);
    CHECK (cmd, MUL,  code, ip);
    CHECK (cmd, JB,   code, ip);
    CHECK (cmd, JA,   code, ip);
    CHECK (cmd, JAE,  code, ip);
    CHECK (cmd, JBE,  code, ip);
    CHECK (cmd, JE,   code, ip);
    CHECK (cmd, JNE,  code, ip);
    CHECK (cmd, JMP,  code, ip);
    CHECK (cmd, HLT,  code, ip);
    CHECK (cmd, RET,  code, ip);
    CHECK (cmd, IN,   code, ip);
    CHECK (cmd, SQRT, code, ip);
    
    if (strchr (cmd, ':') != NULL) return LABEL;
    if (strcmp (cmd, "CALL") == 0) return CALL;
    
    printf ("syntax error - %s\n", cmd); 
    return bad_str;
}
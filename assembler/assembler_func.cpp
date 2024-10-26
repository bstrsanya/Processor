#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "asm_func.h"

void ReadAsm (str_asm* asm_data) //TODO use onegin
{
    while (1)
    {
        char cmd[LEN_COMMAND] = "";
        if (fscanf (asm_data->file_input, "%s", cmd) == EOF) break;

        if (strchr (cmd, ':') != NULL) PutLabel (asm_data->labels, &(asm_data->ip), cmd); 
        else 
        {
            int code_cmd = CompilationCommand (asm_data->code, &(asm_data->ip), cmd);

            switch (code_cmd) {

                case (PUSH):
                case (POP):
                case (JB):
                case (JBE):
                case (JA):
                case (JAE):
                case (JE):
                case (JNE):
                case (JMP):
                case (CALL): 
                    WorkArg (asm_data->file_input, asm_data->code, &(asm_data->ip), asm_data->labels);
                    break; 
                
                case AX:
                case BX:
                case CX:
                case DX:
                case SUB:
                case ADD:
                case DIV:
                case OUT:
                case MUL:
                case RET:
                case IN:
                case SQRT:
                case DRAW:
                case HLT:
                case ERR:
                case PUTC:
                    break;

                case BAD_STR:
                default: 
                    printf ("Try again\n");
                    break;
            }

        }
    }
}

int FindLabel (char* arg, int* code, int* ip, struct STR_labels* labels)
{
    if (strchr (arg, ':') != NULL) //TODO "sasas:sdasdasd ::fsafsafdas" - is error of user
    {
        arg [(int) (strchr (arg, ':') - &arg[0])] = ' ';
        for (int count = 0; count < LEN_LABELS; count++)
            if (strcmp (arg, labels[count].name_label) == 0)
            {
                code[(*ip)++] = labels[count].ptr_label;
                return 1;
            }
    }
    else
        {code[(*ip)++] = atoi (arg); return 1;}
    return 0;
}

void PutLabel (STR_labels *labels, int* ip, char* cmd)
{
    cmd [(strchr (cmd, ':') - &cmd[0])] = ' ';

    for (int count = 0; count < LEN_LABELS; count++)
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
    {
        if (isdigit (str[i])) return atoi (&str[i]);
    } 

    return -1;
}

void WorkArg (FILE* file_input, int* code, int* ip, STR_labels* labels)
{
    char arg[LEN_COMMAND] = "";
    fscanf (file_input, "%s", arg);

    int n_push   = 0;
    int n_reg    = 0;
    int im_const = MyAtoi (arg, (int) strlen (arg));

    if (strchr (arg, ':') != NULL) 
    {
        if (FindLabel (arg, code, ip, labels) == 0) code[(*ip)++] = -1;
    }
    else {
    if ((strchr (arg, '[') != NULL) && (strchr (arg, ']') != NULL)) n_push |= MASK_MEM;

    char* ptr;
    if ((ptr = strchr (arg, 'X')) != NULL) {n_push |= MASK_REG; n_reg = *(ptr-1) - 'A' + 1;}
    //TODO строку sadasdasdas1sdfdsax - ошибка пользователя и её нужно отлавливать, значит строку нужно проверять тщательнее
    //TODO можно вынести в отдельную функцию наложение маски
    
    if (im_const != -1) n_push |= MASK_CON; //TODO not use magic-const NOn valid value; -1 - valid value

    code[(*ip)++] = n_push; //TODO use mask on command

    if (im_const != -1) code[(*ip)++] = im_const; //TODO объединить if
    if (n_reg != 0) code[(*ip)++] = n_reg;}
}

int CompilationCommand (int* code, int* ip, char* cmd)
{
    #define CHECK_(cmd, arg, code, ip)          \
    do {                                        \
        if (strcmp (cmd, #arg) == 0) {          \
            code[(*ip)++] = arg; return arg;    \
        }                                       \
                                                \
    } while(0)

    CHECK_(cmd, PUSH, code, ip);
    CHECK_(cmd, POP,  code, ip);
    CHECK_(cmd, SUB,  code, ip);
    CHECK_(cmd, ADD,  code, ip);
    CHECK_(cmd, DIV,  code, ip);
    CHECK_(cmd, OUT,  code, ip);
    CHECK_(cmd, MUL,  code, ip);
    CHECK_(cmd, JB,   code, ip);
    CHECK_(cmd, JA,   code, ip);
    CHECK_(cmd, JAE,  code, ip);
    CHECK_(cmd, JBE,  code, ip);
    CHECK_(cmd, JE,   code, ip);
    CHECK_(cmd, JNE,  code, ip);
    CHECK_(cmd, JMP,  code, ip);
    CHECK_(cmd, HLT,  code, ip);
    CHECK_(cmd, RET,  code, ip);
    CHECK_(cmd, IN,   code, ip);
    CHECK_(cmd, SQRT, code, ip);
    CHECK_(cmd, DRAW, code, ip);
    CHECK_(cmd, CALL, code, ip);
    CHECK_(cmd, PUTC, code, ip);

    printf ("syntax error - %s\n", cmd);
    return BAD_STR;

    #undef CHECK_
}


void DoubleCompilation (str_asm* asm_data)
{
    ReadAsm (asm_data);
    if (fseek (asm_data->file_input, 0, SEEK_SET)) printf ("error fseek\n");
    asm_data->ip = 0;
    ReadAsm (asm_data);
}

void AsmDtor (str_asm* asm_data)
{
    free (asm_data->labels); asm_data->labels = NULL;
    free (asm_data->code); asm_data->code = NULL;
    free (asm_data); asm_data = NULL;
}

str_asm* AsmCtor (FILE* file_input)
{
    STR_labels* labels = (STR_labels*) calloc (LEN_LABELS, sizeof (STR_labels));

    for (int i = 0; i < LEN_LABELS; i++)
        labels[i] = {};

    int* arr_code = (int*) calloc (LEN_CODE, sizeof (int));
    str_asm* asm_data = (str_asm*) calloc (1, sizeof (str_asm));

    asm_data->code = arr_code;
    asm_data->file_input = file_input;
    asm_data->ip = 0;
    asm_data->labels = labels;

    return asm_data;
}

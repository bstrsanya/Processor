#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "asm_func.h"

int ReadAsm (str_asm* asm_data)
{
    while (1)
    {
        char cmd[LEN_COMMAND] = "";
        int count = 0;

        if (asm_data->ptr < asm_data->size_file)
        {
            sscanf (asm_data->array_code + asm_data->ptr, "%[^\r]%n", cmd, &count);
        }
        else break;

        asm_data->ptr += count + 2;

        char s1[LEN_COMMAND] = "";
        char s2[LEN_COMMAND] = "";
        char s3[LEN_COMMAND] = "";

        sscanf (cmd, "%s %s %s", s1, s2, s3);
        if (s1[0] == 0 && s2[0] == 0 && s3[0] == 0) continue; // пустая строка

        if (s3[0] != 0)
        {
            printf ("[%s] - WRONG STR", s3);
            return WRONG_STR;
        }

        if ((IsLabel (cmd) == RIGHT_LABEL) && (s2[0] == 0) && (s3[0] == 0))
        {
            PutLabel (asm_data->labels, &(asm_data->ip), cmd); 
        }
        else if (IsLabel (cmd) == WRONG_LABEL) 
        {
            return WRONG_LABEL;
        }
        else 
        {
            int code_cmd = CompilationCommand (asm_data->code, &(asm_data->ip), s1);

            switch (code_cmd) {

                case (PUSH):       //Command has argument 
                case (POP):
                case (JB):
                case (JBE):
                case (JA):
                case (JAE):
                case (JE):
                case (JNE):
                case (JMP):
                case (CALL): {
                    int code_err = WorkArg (asm_data, s2);
                    if (code_err != ARG_OK)
                        return code_err; }
                    break; 
                                 //Command has not argument 
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
                case OUTC:
                    break;

                case WRONG_CMD:
                default: 
                    return WRONG_CMD;
                    printf ("Try again\n");
                    break;
            }

        }
    }
    return READ_OK;
}

int FindLabel (char* arg, int* code, int* ip, struct STR_labels* labels)
{
    if (IsLabel (arg) == RIGHT_LABEL) 
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
    {
        code[(*ip)++] = atoi (arg); return 1;
    }

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
        if (isdigit (str[i]))
        {
            double digit = 0;
            sscanf (&str[i], "%lf", &digit);
            return (int) (digit * PRECISION);
        }
    } 

    return NOT_NUMBER;
}

int WorkArg (str_asm* asm_data, char* arg)
{
    if (IsLabel (arg) == RIGHT_LABEL) 
    {
        if (FindLabel (arg, asm_data->code, &(asm_data->ip), asm_data->labels) == 0) 
            asm_data->code[(asm_data->ip)++] = -1;
    }
    else 
    {
        int n_push   = 0;
        int n_reg    = 0;
        int im_const = MyAtoi (arg, (int) strlen (arg));

        int code_err = CreatMask (arg, &n_push, &n_reg, &im_const);
        if (code_err != RIGHT_MASK) return code_err;

        CreatCode (asm_data->code, &(asm_data->ip), n_push, im_const, n_reg);
    }
    return ARG_OK;
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
    CHECK_(cmd, OUTC, code, ip);

    printf ("syntax error - %s\n", cmd);
    return WRONG_CMD;

    #undef CHECK_
}

int DoubleCompilation (str_asm* asm_data)
{
    int ret = ReadAsm (asm_data);
    if (ret != READ_OK) return ret;

    asm_data->ptr = 0;
    asm_data->ip = 0;

    ReadAsm (asm_data);
    return COMPL_OK;
}

void AsmDtor (str_asm* asm_data)
{
    free (asm_data->labels); asm_data->labels = NULL;
    free (asm_data->code); asm_data->code = NULL;
    free (asm_data->array_code); asm_data->array_code = NULL;
    free (asm_data); asm_data = NULL;
}

str_asm* AsmCtor (FILE* file_input)
{
    STR_labels* labels = (STR_labels*) calloc (LEN_LABELS, sizeof (STR_labels));

    for (int i = 0; i < LEN_LABELS; i++)
        labels[i] = {};

    int* arr_code = (int*) calloc (LEN_CODE, sizeof (int));
    str_asm* asm_data = (str_asm*) calloc (1, sizeof (str_asm));

    size_t size = 0;
    char* massive = ReadFile (file_input, &size);

    asm_data->code = arr_code;
    asm_data->array_code = massive;
    asm_data->ptr = 0; // относится к array_code
    asm_data->ip = 0; // относится к code
    asm_data->labels = labels;
    asm_data->size_file = (int) size;

    return asm_data;
}

int IsLabel (char* arg)
{   
    char* ptr = strchr (arg, ':');
    if (ptr != NULL)
    {
        if (*(ptr + 1) != 0) 
            return WRONG_LABEL;
        else
            return RIGHT_LABEL;
    }
    else
        return NOT_LABEL;
}

int CreatMask (char* arg, int* n_push, int* n_reg, int* im_const)
{
    if ((strchr (arg, '[') != NULL) && (strchr (arg, ']') != NULL)) 
    {
        *n_push |= MASK_MEM;
    }

    char* ptr = strchr (arg, 'X');
    if (ptr != NULL) 
    {
        *n_reg = *(ptr-1) - 'A' + 1;
        if ((0 < *n_reg) && (*n_reg < NUM_REG))
            *n_push |= MASK_REG; 
        else 
            return WRONG_REG;
    }
    
    if (*im_const != NOT_NUMBER) 
    {
        *n_push |= MASK_CON; 
    }

    if (*n_push == 0) return WRONG_ARG;
    return RIGHT_MASK;
}

void CreatCode (int* code, int* ip, int n_push, int im_const, int n_reg)
{
    code[(*ip)++] = n_push; 
    if (im_const != NOT_NUMBER) 
        code[(*ip)++] = im_const; 
    if (n_reg != 0) 
        code[(*ip)++] = n_reg;
}
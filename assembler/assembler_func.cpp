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
        char cmd[len_command] = ""; //TODO caps for constant
        command code_cmd = CompilationCommand (asm_data->file_input, asm_data->code, &(asm_data->ip), cmd);

        if (code_cmd == err) break;
        switch (code_cmd) {
//TODO
            case (PUSH):
            case (POP): {
                char arg[len_command] = "";
                fscanf (asm_data->file_input, "%s", arg); //TODO напиши функцию определения аргументов(всех)

                int n_push   = 0;
                int n_reg    = 0;
                int im_const = MyAtoi (arg, (int) strlen (arg));

                WorkArg (arg, &n_push, &n_reg, &im_const, asm_data->code, &(asm_data->ip));
                if ((code_cmd == POP) && (n_push == 1))  {printf ("pop %d - illegal operation\n", im_const); assert (0);} //TODO убрать костыль
                break; }

            case (LABEL): {
                PutLabel (asm_data->labels, &(asm_data->ip), cmd); //TODO label is not command определяй и работай с ними отдельно
                break; }

            case (JB):
            case (JBE):
            case (JA):
            case (JAE):
            case (JE):
            case (JNE):
            case (JMP): {
                if (!FindLabel (asm_data->file_input, asm_data->code, &(asm_data->ip), asm_data->labels)) asm_data->code[(asm_data->ip)++] = -1;
                break; } //TODO поместить в функцию work_arg

            case (CALL): {
                asm_data->code[(asm_data->ip)++] = CALL; //TODO поместить в функцию work_arg
                if (!FindLabel (asm_data->file_input, asm_data->code, &(asm_data->ip), asm_data->labels)) asm_data->code[(asm_data->ip)++] = -1;
                break; }


            case (bad_str): { //TODO CAPS for const
                printf ("Try again\n");
                assert (0);  } //TODO assert not for user
            
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
            case len_code:
            case err:
                break;

            default: break;

        }
    }
}

int FindLabel (FILE* file_input, int* code, int* ip, struct STR_labels* labels)
{
    char label[len_command] = "";
    fscanf (file_input, "%s", label);

    if (strchr (label, ':') != NULL) //TODO "sasas:sdasdasd ::fsafsafdas" - is error of user
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

void PutLabel (STR_labels *labels, int* ip, char* cmd)
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
    for (int i = 0; i < size; i++) {
        if (isdigit (str[i])) return atoi (&str[i]);
    } //TODO use {}

    return -1;
}

void WorkArg (char* arg, int* n_push, int* n_reg, int* im_const, int* code, int* ip)
{
    if ((strchr (arg, '[') != NULL) && (strchr (arg, ']') != NULL)) *n_push |= MASK_MEM;

    if (strstr (arg, "AX") != NULL) {*n_push |= MASK_REG; *n_reg = AX;} //TODO строку sadasdasdas1sdfdsax - ошибка пользователя и её нужно отлавливать, значит строку нужно проверять тщательнее
    if (strstr (arg, "BX") != NULL) {*n_push |= MASK_REG; *n_reg = BX;}
    if (strstr (arg, "CX") != NULL) {*n_push |= MASK_REG; *n_reg = CX;} //TODO use one if
    if (strstr (arg, "DX") != NULL) {*n_push |= MASK_REG; *n_reg = DX;} //TODO можно вынести в отдельную функцию наложение маски
    //ax bx
    //r%cx
    if (*im_const != -1) *n_push |= MASK_CON; //TODO not use magic-const NOn valid value; -1 - valid value

    code[(*ip)++] = *n_push; //TODO use mask on command

    if (*im_const != -1) code[(*ip)++] = *im_const; //TODO объединить if
    if (*n_reg != 0) code[(*ip)++] = *n_reg;
}

command CompilationCommand (FILE* file_input, int* code, int* ip, char* cmd)
{
    #define CHECK_(cmd, arg, code, ip)          \
    do {                                        \
        if (strcmp (cmd, #arg) == 0) {          \
            code[(*ip)++] = arg; return arg;    \
        }                                       \
                                                \
    } while(0) //TODO

    if (fscanf (file_input, "%s", cmd) == EOF) return err;

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

    if (strchr (cmd, ':') != NULL) return LABEL; //TODO вынести из функции

    printf ("syntax error - %s\n", cmd);
    return bad_str;

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
    memset (asm_data, 0, sizeof (*asm_data));
    asm_data->ip = 0;
}

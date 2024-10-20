#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>

#include "asm_func.h"
#include "processor.h"

#define CHECK(cmd, arg, code, ip) {if (strcmp (cmd, #arg) == 0) {code[(*ip)++] = arg; return arg;}}
//#define CHECK1(arg, str, n_push, n_reg) {if (strstr (arg, #str) != NULL) {n_push |= 2; n_reg = str;}
//#define CHECK2(cmd, arg, code, ip, file_input, labels) {if (strcmp (cmd, #arg) == 0) {code[ip++] = arg; FindMark (file_input, code, &ip, labels); continue;}}
// fread -> sscanf
void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input)
{
    int ip = 0;  // вначале положить все команды в массив 
        // заканчивать прогу когда конец файла, а не hlt +
        // hex-формат +
        // WSL  !!! поиграться с памятью 
        // address sanitize (должен идти с WSL)
        // !расширение! для WSL vs.code
        // TODO: another function with strcmps + switch case +
        // при увеличении регистров не менять прогу
        // switch (CODE_CMD):
        // case PUS
    while (1)
    {
        command code_cmd = ReadCommand (file_input, code, &ip);

        if (code_cmd == err) break;
        switch (code_cmd) {
        
            case (PUSH): case (POP): {
                char arg[30] = "";
                fscanf (file_input, "%s", arg);

                int n_push   = 0;
                int n_reg    = 0;
                int im_const = MyAtoi (arg, strlen (arg));

                WorkArg (arg, &n_push, &n_reg, &im_const, code, &ip);  
                if ((code_cmd == POP) && (n_push == 1))  {printf ("pop %d - illegal operation\n", im_const); assert (0);}
                break; }

            case (MARK): {
                char cmd[len_command] = "";
                fscanf (file_input, "%s", cmd);
                cmd [(strchr (cmd, ':') - &cmd[0])] = ' ';
                for (int count = 0; count < len_labels; count++)
                {
                    if (labels[count].free == 0)
                    {
                        labels[count].free = 1;
                        strcpy (labels[count].name_mark, cmd);
                        labels[count].ptr_mark = ip;
                        break;
                    }
                }
                break;}

            case (JB): case (JBE): case (JA): case (JAE): case (JE): case (JNE): case (JMP): {
                FindMark (file_input, code, &ip, labels);
                break; }

            case (bad_str): {
                printf ("Try aggain\n");
                assert (0); }
        }
    }
      
}

void FindMark (FILE* file_input, int* code, int* ip, struct STR_labels* labels)
{
    char metka[len_command] = "";
    fscanf (file_input, "%s", metka);

    if (strchr (metka, ':') != NULL)
    {
        metka [(int) (strchr (metka, ':') - &metka[0])] = ' ';
        for (int count = 0; count < len_labels; count++)
            if (strcmp (metka, labels[count].name_mark) == 0)
            {
                code[(*ip)++] = labels[count].ptr_mark;
                break;
            }
    }
    else
        code[(*ip)++] = atoi (metka);
}

int MyAtoi (char* str, int size)
{
    char str_copy[30] = "";
    strcpy (str_copy, str);
    for (int i = 0; i < size; i++)
        if ((48 <= (int) str[i]) && ((int) str[i] <= 57))
        {
            for (int j = 0; j < i; j++)
                str_copy[j] = ' ';
            return atoi (str_copy);
        }
    return -1;   
}

void WorkArg (char* arg, int* n_push, int* n_reg, int* im_const, int* code, int* ip)
{
    if ((strchr (arg, '[') != NULL) && (strchr (arg, ']') != NULL)) *n_push |= 4;

    if (strstr (arg, "AX") != NULL) {*n_push |= 2; *n_reg = AX;}
    if (strstr (arg, "BX") != NULL) {*n_push |= 2; *n_reg = BX;}
    if (strstr (arg, "CX") != NULL) {*n_push |= 2; *n_reg = CX;}
    if (strstr (arg, "DX") != NULL) {*n_push |= 2; *n_reg = DX;}

    if (*im_const != -1) *n_push |= 1;
    
    code[(*ip)++] = *n_push;
    if (*im_const != -1) code[(*ip)++] = *im_const;
    if (*n_reg != 0) code[(*ip)++] = *n_reg; 
}

command ReadCommand (FILE* file_input, int* code, int* ip)
{
    char cmd[len_command] = "";
    if (fscanf (file_input, "%s", cmd) == EOF) return err;

    CHECK (cmd, PUSH, code, ip);
    CHECK (cmd, POP, code, ip);
    CHECK (cmd, SUB, code, ip);
    CHECK (cmd, ADD, code, ip);
    CHECK (cmd, DIV, code, ip);
    CHECK (cmd, OUT, code, ip);
    CHECK (cmd, MUL, code, ip);
    CHECK (cmd, JB, code, ip);
    CHECK (cmd, JA, code, ip);
    CHECK (cmd, JAE, code, ip);
    CHECK (cmd, JBE, code, ip);
    CHECK (cmd, JE, code, ip);
    CHECK (cmd, JNE, code, ip);
    CHECK (cmd, JMP, code, ip);
    CHECK (cmd, HLT, code, ip);


    if (strcmp (cmd, "m") == 0) return MARK;
    
    printf ("syntax error - %s\n", cmd); return bad_str;
}
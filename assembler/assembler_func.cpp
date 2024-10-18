#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"
#include "processor.h"

#define CHECK(cmd, arg, code, ip) {if (strcmp (cmd, #arg) == 0) {code[ip++] = arg; continue;}}

void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input)
{
    int ip = 0;  // вначале положить все команды в массив 

    while (1)
    {
            
        char cmd[len_command] = "";
        fscanf (file_input, "%s", cmd);

        if (strcmp (cmd, "hlt") == 0)
        {
            code[ip++] = hlt;
            break;
        }

        if (strcmp (cmd, "push") == 0)
        {
            code[ip++] = push;
            char arg[30] = "";
            fscanf (file_input, "%s", arg);

            if (strchr (arg, '[') == NULL) 
            {
                if ((atoi (arg)) == 0)
                {
                    if (strchr (arg, '+') == NULL)    // push AX
                    {
                    code[ip++] = 2;
                    CHECK (arg, AX, code, ip);
                    CHECK (arg, BX, code, ip);
                    CHECK (arg, CX, code, ip);
                    CHECK (arg, DX, code, ip);
                    }
                    else                              // push AX+1
                    {
                        code[ip++] = 3;
                        char reg_s[3] = "";
                        reg_s[0] = arg[0];
                        reg_s[1] = arg[1];
                        arg[0] = ' '; arg[1] = ' '; arg[2] = ' ';
                        code[ip++] = atoi (arg);
                        CHECK (reg_s, AX, code, ip);
                        CHECK (reg_s, BX, code, ip);
                        CHECK (reg_s, CX, code, ip);
                        CHECK (reg_s, DX, code, ip);
                        
                    }
                }
                else                                   // push 1
                {
                    code[ip++] = 1;
                    code[ip++] = atoi (arg);
                }
            }
            else                                        
            {
                char reg_s[3] = "";
                reg_s[0] = arg[1];
                reg_s[1] = arg[2];
                arg[0] = ' ';
                if (strchr (arg, '+') == NULL)         
                {
                    if ((atoi (arg)) == 0)             // push [CX]
                    {
                        code[ip++] = 6;
                        CHECK (reg_s, AX, code, ip);
                        CHECK (reg_s, BX, code, ip);
                        CHECK (reg_s, CX, code, ip);
                        CHECK (reg_s, DX, code, ip);
                    }
                    else                               // push [1]
                    {
                        code[ip++] = 5;
                        code[ip++] = atoi (arg);
                        
                    }
                }
                else                                   // push CX+5
                {
                    arg[1] = ' '; arg[2] = ' '; arg[3] = ' ';
                    int num = atoi (arg);
                    code[ip++] = 7;
                    code[ip++] = num;
                    CHECK (reg_s, AX, code, ip);
                    CHECK (reg_s, BX, code, ip);
                    CHECK (reg_s, CX, code, ip);
                    CHECK (reg_s, DX, code, ip);
                }
            }
            continue;
        }

        CHECK(cmd, sub, code, ip);
        CHECK(cmd, add, code, ip);
        CHECK(cmd, DIV, code, ip);
        CHECK(cmd, out, code, ip);
        CHECK(cmd, mul, code, ip);

        if (strcmp (cmd, "pop") == 0)
        {
            code[ip++] = pop;

            char num[10] = "";
            fscanf (file_input, "%s", num);
            
            if (strcmp (num, "AX") == 0)
                code[ip++] = AX;
            
            if (strcmp (num, "BX") == 0)
                code[ip++] = BX;
            
            if (strcmp (num, "CX") == 0)
                code[ip++] = CX;
            
            if (strcmp (num, "DX") == 0)
                code[ip++] = DX;
            continue;
        }

        if (strcmp (cmd, "jb") == 0)
        {
            code[ip++] = jb;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "ja") == 0)
        {
            code[ip++] = ja;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "jae") == 0)
        {
            code[ip++] = jae;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "jbe") == 0)
        {
            code[ip++] = jbe;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "je") == 0)
        {
            code[ip++] = je;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "jne") == 0)
        {
            code[ip++] = jne;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if (strcmp (cmd, "jmp") == 0)
        {
            code[ip++] = jmp;
            FindMark (file_input, code, &ip, labels);
            continue;
        }

        if ((strchr (cmd, ':') != NULL))
        {
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
            continue;
        }        
        printf ("Syntax error: '%s'\n", cmd);
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

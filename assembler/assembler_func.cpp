#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "asm_func.h"
#include "processor.h"

void Read_Asm (int* code, struct STR_labels* labels, FILE* file_input)
{
    int ip = 0;

    while (1)
    {
        char cmd[len_command] = "";
        fscanf (file_input, "%s", cmd);

        if (strcmp (cmd, "push") == 0)
        {
            code[ip++] = push;
            int arg = 0;
            fscanf (file_input, "%d", &arg);
            code[ip++] = arg;
            continue;
        }

        if (strcmp (cmd, "sub") == 0)
        {
            code[ip++] = sub;
            continue;
        }

        if (strcmp (cmd, "add") == 0)
        {
            code[ip++] = add;
            continue;
        }

        if (strcmp (cmd, "DIV") == 0)
        {
            code[ip++] = DIV;
            continue;
        }

        if (strcmp (cmd, "out") == 0)
        {
            code[ip++] = out;
            continue;
        }

        if (strcmp (cmd, "mul") == 0)
        {
            code[ip++] = mul;
            continue;
        }

        if (strcmp (cmd, "hlt") == 0)
        {
            code[ip++] = hlt;
            break;
        }

        if (strcmp (cmd, "pushr") == 0)
        {
            code[ip++] = pushr;
            char num[10] = "";
            fscanf (file_input, "%s", num);
            
            if (strcmp(num, "AX") == 0)
                code[ip++] = AX;
            
            if (strcmp(num, "BX") == 0)
                code[ip++] = BX;
            
            if (strcmp(num, "CX") == 0)
                code[ip++] = CX;
            
            if (strcmp(num, "DX") == 0)
                code[ip++] = DX;
            continue;
        }

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
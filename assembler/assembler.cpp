#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "processor.h"

int main()
{
    FILE *file_input = fopen ("program.asm", "rb");
    FILE *file_output = fopen ("program_code.bin", "wb");

    int labels[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    int code[100] = {};
    int ip = 0;

    while (1)
    {
        char cmd[30] = "";
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
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            if (fgetc(file_input) == ':')
                code[ip++] = labels[shift];
            else
                code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "ja") == 0)
        {
            code[ip++] = ja;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "jae") == 0)
        {
            code[ip++] = jae;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "jbe") == 0)
        {
            code[ip++] = jbe;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "je") == 0)
        {
            code[ip++] = je;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "jne") == 0)
        {
            code[ip++] = jne;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if (strcmp (cmd, "jmp") == 0)
        {
            code[ip++] = jmp;
            int shift = 0;
            fscanf (file_input, "%d", &shift);
            code[ip++] = shift;
            continue;
        }

        if ((int) cmd[1] == 58)
        {
            labels[atoi (cmd)] = ip;
            continue;
        }         

        printf ("Syntax error: '%s'\n", cmd);
    }

    fwrite (code, sizeof (code[0]), sizeof (code) / sizeof (code[0]), file_output);
    fclose (file_input);
    fclose (file_output);
}
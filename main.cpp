#include <stdio.h>


int main()
{
    char str[20] = "[CX + 5]";
    int num = 0;
    char c = 0;
    sscanf (str, "%*c %*c %c %*c %d", &c, &num);
    printf ("c = [%c]; num = [%d]", c, num);
}
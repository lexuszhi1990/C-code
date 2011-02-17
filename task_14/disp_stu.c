#include <stdio.h>
#include "main.h"
void disp_stu(stu p)
{
    printf("num\t\t\tname\n");
    printf("total num:");
    while (p) 
    {
        printf("%-10d%s\n", p->num, p->name);
        p = p->next;
    }
}

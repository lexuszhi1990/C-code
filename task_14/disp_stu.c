#include <stdio.h>
#include "main.h"
void disp_stu(stu p)
{
    int total = 0;
    printf("num :\t\tname :\n");
    while (p) 
    {
        printf("%-15d%s\n", p->num, p->name);
        p = p->next;
        total++;
    }
	printf("%-15s%s\n","class name:","class 2 grade 3");
	printf("%-15s%d\n","total num :",total);
}

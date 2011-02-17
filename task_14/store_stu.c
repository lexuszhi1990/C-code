#include <stdio.h>
#include "main.h"
void store_stu(stu p)
{
    FILE *fp =NULL;
    fp = fopen("tex.txt", "w+");
    stu_check(fp);
    while (p != NULL) 
    {
        fprintf(fp, "%-10d%s", p->num, p->name);
        p = p->next;
    }
    printf("stored successfully!\n");
    return ;
}

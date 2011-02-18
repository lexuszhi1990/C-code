#include <stdio.h>
#include "main.h"
stu del_stu(stu p)
{
    if (p == NULL) 
    {
        printf("empty!\n");
        return p;
    }
    printf("please input a stu num\n");
    int num;
    scanf("%d",&num);
    getchar();
    stu *pstu;
    pstu = &p;
    for (; *pstu; pstu = &(*pstu)->next) 
    {
        if ((*pstu)->num == num) 
        {
            printf("%-5d%s has be deleted!\n", (*pstu)->num, (*pstu)->name);
            (*pstu) = (*pstu)->next;
             return p;
        }
    }
    printf("no this num\n");
}

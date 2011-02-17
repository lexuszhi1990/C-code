#include <stdio.h>
#include "main.h"
void del_stu(stu p)
{
    printf("please input a stu num\n");
    int num;
    scanf("%d",&num);
    getchar();
    stu *pstu;
    pstu = &(p->next);
    for (; *pstu; pstu = &(*pstu)->next) 
    {
        if ((*pstu)->num == num) 
        {
            (*pstu) = (*pstu)->next;
             return ;
        }
    }
    printf("no this num\n");
}

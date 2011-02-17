#include <stdio.h>
#include "main.h"
stu del_stu(stu p)
{
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
            (*pstu) = (*pstu)->next;
		total--;
             return p;
        }
    }
    printf("no this num\n");
}

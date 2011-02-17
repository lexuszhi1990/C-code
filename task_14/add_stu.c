#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void same_stu(stu p, stu *pstu)
{
    char flag = 0;
    printf("%-10d %s is already exit!!!\n", p->num,p->name);
    printf("replace? ,input y or n \n");
    scanf("%c", &flag);
    getchar();
    if (flag == 'y') 
    {
        p->next = (*pstu)->next;
        *pstu = p;
        printf("replaced!\n");
    }
                return ;
}

void suc_stu(stu p)
{
    printf("%d %s has be added\n", p->num,p->name);
    total++;
     printf("%d\n", total);
}
stu get_stu(stu p)
{
    p = stu_malloc(p);
    printf("please input a stu-num(back input 9):\n");
    scanf("%d", &p->num);
    getchar();
    if(p->num == 9) 
        {
            free(p);
            return p;
        }
    printf("please input a student name\n");
    scanf("%s", p->name);
    getchar();
    p->next = NULL;
    return p;
}

stu put_stu(stu head, stu p)
{
    if (head->num == -1) 
    {
	free(head);
        suc_stu(p);
        return p;
    }
    stu *pstu;
    for (pstu = &head; *pstu; pstu = &(*pstu)->next) 
    {
        if (p->num ==(*pstu)->num) 
        {
            same_stu(p, pstu);
            return head;
        }
        if ( p->num < (*pstu)->num) 
        {
            p->next = (*pstu);
            (*pstu) = p;
            suc_stu(p);
            return head;
        }
    }
    (*pstu) = p;
    suc_stu(p);
    return head;
}

stu add_stu( stu head )
{
    stu p;
    p = get_stu(p);
    if (p->num == 9) 
    {
        free(p);
        return head;
    }
    head = put_stu(head, p);
    return head;
}

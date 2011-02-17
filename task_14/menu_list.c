#include <stdio.h>
#include "main.h"
int  menu_list(void)
{
    printf("please input a choice num:\n");
    printf("1 : add stu\n");
    printf("2 : delete stu\n");
    printf("3 : display stu\n");
    printf("4 : store stu\n");
    printf("5 : get stu\n");
    printf("9 : quit\n");
    int  c ;
    scanf("%d", &c);
    getchar();
    return  c;
}

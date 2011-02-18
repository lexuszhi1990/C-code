#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
stu read_stu(void)
{
    FILE *fp = NULL;
    int number = 0;
    char na[20];
    stu p = NULL;
    fp = fopen("tex.txt","a+");
    if (fp == NULL) 
    {
        fp = fopen("tex.txt","a+");
        stu_check(fp);
	if (fp ==NULL) 
	{
		printf("file failed\n");
		return ;
	}
	
    }
    if (fscanf(fp , "%d%s", &number, na) != EOF) 
    {
        p = malloc(sizeof(struct student));
        stu_check(p);
        p->num = number;
        strncpy(p->name, na , 14);
        p->next = NULL;
    }
	else {
		return NULL;
		printf("file is empty!\n");
	}
    stu head = p;
	int i = 0;
	printf("%ld\n",ftell(fp));
    while (fscanf(fp , "%d%s", &number, na) != EOF) 
    {
        p->next = malloc(sizeof(struct student));
        stu_check(p->next);
        p->next->num = number;
        strncpy(p->next->name, na , 14);
        p->next->next = NULL;
        p = p->next;
    }
    printf("read successfully!\n");
    disp_stu(head);
    fclose(fp);
    return head;
}

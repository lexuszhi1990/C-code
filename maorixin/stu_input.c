#include "common.h"

extern stu *head;

void stu_in( stu *p)
{
    char buf[BUF];  
    int n = 0;
    if (p == NULL) {
        p = (stu *) malloc( sizeof( struct student));
        if (p == NULL) {
            return  ;
        }
    }

    printf("input the student name  :\n");
    scanf("%s", buf);
    n = strlen(buf);
    p->name = (char *) malloc(n + 1);
    if (p->name ==NULL) {
        perror("malloc name wrong");
        exit(0);
    }
    strncpy(p->name, buf, n);
    p->name[n] = '\0';

    printf("input the school_year :\n");
    scanf("%s", buf);
    n = strlen(buf);
    p->school_year = (char *) malloc( n + 1);
    if (p->school_year == NULL) {
        perror("malloc sh_year wrong");
        exit(1);
    }
    strncpy(p->school_year, buf, n);
    p->school_year[n] = '\0';
    printf("%s\n",p->school_year);

    printf("please input your academy :\n");
    scanf("%s", buf);
    n = strlen(buf);
    p->academy = (char *) malloc( n + 1);
    if (p->academy == NULL) {
        perror("malloc sh_year wrong");
        exit(1);
    }
    strncpy(p->academy, buf, n);
    p->academy[n] = '\0';
    printf("%s\n",p->academy);

    printf("please input your profession :\n");
    scanf("%s", buf);
    n = strlen(buf);
    p->profession = (char *) malloc( n + 1);
    if (p->profession == NULL) {
        perror("malloc profession wrong");
        exit(1);
    }
    strncpy(p->profession, buf, n);
    p->profession[n] = '\0';
    printf("%s\n",p->profession);

    printf("please input your class :\n");
    scanf("%s", buf);
    n = strlen(buf);
    p->class = (char *) malloc( n + 1);
    if (p->class == NULL) {
        perror("malloc class wrong");
        exit(1);
    }
    strncpy(p->class, buf, n);
    p->class[n] = '\0';
    printf("%s\n",p->class);

    printf("please input your score :\n");
    int sco = 0;
    scanf("%d",&sco);
    p->score = (unsigned int )sco;
    printf("%d\n",p->score);

    p->next = NULL;
    printf("input finished\n");
    stu_disp(p);
}

stu *stu_import(stu *head)
{
    char s = 0;
    stu *p, *q;
    printf("start to build student list\n");

    if (head == NULL) {
        p = (stu *)malloc( sizeof(struct student));
        stu_in(p);
        head = p;
        printf("continued input 'c', back to menu input other key\n");
        getchar();
        scanf("%c", &s);
        getchar();
        if (s == 'c') {
            goto input_again;
        } else {
            return head;
        }
    }
input_again:
    p = (stu *)malloc( sizeof(struct student));
    stu_in(p);
    q = head;
    while (q->next != NULL){
        q = q->next;
    }
    q->next = p;
    printf("continued press 'c', back to menu input other key\n");
    getchar();
    scanf("%c", &s);
    getchar();
    if (s == 'g') {
        goto input_again;
    }else {
        return head;
    }
}

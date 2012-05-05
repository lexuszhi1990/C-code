#include "common.h"

extern void *stu_in(stu *);

extern stu *head;
void stu_insert_end(void)
{
    stu *p, *q;
    q = head;

    p = (stu *)malloc( sizeof(struct student));
    if (p == NULL) {
        perror("insert end error");
        return  ;
    }
 
    stu_in(p);
    if (q == NULL) {
        q = p;
    }else if (q != NULL && p != NULL) {
        while (q->next != NULL){
            q = q->next;
        }
        q->next = p;
    }
    
    return  ;
}

void stu_insert_begin(void)
{
    stu *p;

    p = (stu *)malloc( sizeof(struct student));
    if (p == NULL) {
        return ;
    }
    stu_in(p);
    p->next = head;
    head = p;

    return  ;
}

void stu_insert_default(void)
{
    printf("sorry, no this number...\n");    
}

void stu_insert_put(stu *p, unsigned int i)
{
    stu *s = head;
    unsigned int j = 0;
    
    if (i == 1) {
        p->next = s;
        head = p;
        return  ;
    }
    j = i - 2;
    while (j){
        s = s->next;
        j--;
    }
    p->next = s->next;
    s->next = p;
    return  ;
}


void stu_insert_want(void)
{
    stu *p = head;
    unsigned int i = 0;
    unsigned int m = 0;
    printf("student list as following :\n");
    while (p != NULL){
        printf("no.%dname:%s\t", ++i, p->name);
        if (i == 5) {
            putchar('\n');
        }
        p = p->next;
    }
    putchar('\n');
    i++;
    printf("input the num you want insert... \n");
    printf("such as : you want this student to be the 5th, just input '5'\n");
stu_insert_again:
    scanf("%d",&m);
    getchar();
    if ( m > i) {
        printf("wrong number, please input again\n");
        goto stu_insert_again;
    }
    p = (stu *) malloc ( sizeof(struct student));
    if (p == NULL) {
        perror("insert malloc wrong");
        return  ;
    }
    stu_in(p);
    stu_insert_put(p, m); 

    return ;
}


void stu_insert(void)
{
    int c = 0;
    printf("Insert choices\n");
    printf(" 1 : insert a student at the end of the student list\n");
    printf(" 2 : insert a student at the beginning of the student list\n");
    printf(" 3 : insert a student at what you want...\n");
    printf(" 0 : quit, and back to main menu\n");
    scanf("%d",&c);
    getchar();
    switch ( c ) {
        case 0 : break ;
        case 1 : stu_insert_end();break;
        case 2 : stu_insert_begin();break;
        case 3 : stu_insert_want();break;
        default : stu_insert_default();break;
    }

    return  ;
}



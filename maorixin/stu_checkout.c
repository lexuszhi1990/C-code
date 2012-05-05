#include "common.h"

extern stu *head;

stu *stu_search_by_name(const char *s, unsigned int n)
{
    stu *p = head ;
    while(p != NULL) {
        if ( strncmp(s, p->name, n) == 0) {
            return p; 
        }
        p = p->next;
    }
    return NULL;
}

void stu_checkout_find(void)
{
    char buf[BUF];
    int n = 0;
    stu *p = NULL;
    
    printf("input the name you want to find\n");
    scanf("%s", buf);
    getchar();
    n = strlen(buf);
    buf[n] = 0;
    p = stu_search_by_name(buf, n);
    if (p == NULL) {
        printf("no this student \n");
        return ;
    }
    stu_disp(p);
    return ;
}

void stu_checkout_all(void)
{
    stu *p = head;
    while (p != NULL){
        stu_disp(p);
        p = p->next;
    }
}

void stu_checkout(void )
{
    int n;
    if (head == NULL) {
        printf("there is no student here\n");
        return ;
    }
    printf("checkout list \n");
    printf(" 1 : list all the student\n");
    printf(" 2 : find a student in the list\n");
    printf(" 0 : back to main menu\n");
    scanf("%d", &n);
    getchar();

    switch( n ) {
        case 1 : stu_checkout_all();break;
        case 2 : stu_checkout_find();break;
        case 0 : return;
        default  : break;
    }
    return ; 
}

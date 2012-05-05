#include "common.h"

extern stu *head;

void stu_free(stu *p)
{
    if (p == NULL) {
        printf("no this student\n");
        return ;
    }
    printf("%s student to be freed\n", p->name);
    free(p->name);
    free(p->school_year);
    free(p->academy);
    free(p->profession);
    free(p->class);
    free(p);
    printf("cleaned successfully\n");
}

void stu_clean(void)
{
    stu *p = head;
    stu *q = p->next;
    printf("now, clean all the student\n");
    if (head == NULL) {
        printf("no student\n");
        return ;
    }

    while (1){
        if (q == NULL) {
            printf(" to clean %s student\n", p->name);
            stu_free(p);
            break;
        }
        printf(" to clean %s student\n", p->name);
        stu_free(p);
        p = q;
        q = q->next;
    }
    printf("all cleaned\n");
}

void stu_del_one(void) 
{
    int n = 0;
    char buf[BUF];
    stu *p = NULL;
    stu *q = NULL;
    
    printf("please input the name you want to delete :\n");  
    scanf("%s", buf);
    getchar();
    n = strlen( buf);
    buf[n] = 0;
    printf("name : %s\n", buf);
    
    if ( strncmp(head->name, buf, n) == 0) {
        p = head;
        head = head->next;
        stu_free(p);
        return ;
    }

    p = head;
    while ( 1 ){
        q = p->next;
        if (q == NULL) {
            printf("no this student\n");
            return ;
        }
        if ( strncmp(q->name, buf, n) == 0) {
            p->next = q->next;
            stu_free(q);
            return ;
        }
        p = p->next;
    }

}

void stu_del_all(void)
{
    stu_clean();
    head = NULL;
}

void stu_del_default(void)
{
    printf("no this command of number...\n");
}

void stu_del(void)
{
    unsigned int n = 0;

    printf("delete function list :\n");
    printf(" 1 : delete a student\n");
    printf(" 2 : delete all students\n");
    printf(" 0 : back to main menu\n");
    scanf("%d",&n);
    getchar();
    
    switch ( n ) {
        case 0 : return ;
        case 1 : stu_del_one();break;
        case 2 : stu_del_all();break;
        default : stu_del_default(); return;
    }
#if 0
    stu **pstu;
    pstu = &head;
    for (; *pstu; pstu = &(*pstu)->next) {
        if ( strncmp( (*pstu)->name, buf, n) == 0) {
            printf("%-5d%s has be deleted!\n", (*pstu)->score, (*pstu)->name);
            (*pstu) = (*pstu)->next;
            return (*pstu);
        }
    }
    printf("no this num\n");
    return NULL;
#endif

#if 0
    p = stu_search_by_name(buf, n);
    if (p == NULL) {
        printf("no this student\n");
        printf("input once again press 'r', other key back\n");
        scanf("%c", &s);
        getchar();
        if (s == 'r'){
            goto once;
        }else {
            return NULL;
        }
    }
    if (p == head ) {
        head = head->next;
        stu_free(p);
        return head;
    }
    q = head;
    for( ; q; q = q->next) {
        if (p == q->next) {
            stu_free(p);
            q->next = p->next;
            return head;
        }
    }
#endif
}

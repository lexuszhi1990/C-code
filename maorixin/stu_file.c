#include "common.h"

#define STU_FILE "list.txt"
extern stu *head;

stu *stu_read(void)
{
    FILE *fp = NULL;
    unsigned int n = 0;
    unsigned int m = 0;
    char buf0[128], buf1[128], buf2[128], buf3[128], buf4[128];
    stu *p, *q;

    printf("start to read the student file\n");
    fp = fopen(STU_FILE,"a+");
    if (fp == NULL) {
        fp = fopen(STU_FILE,"a+");
        if (fp ==NULL) {
            perror("file failed...\n");
            return head;
        }
    }
    if ( fgetc(fp) == EOF) {
        return NULL;
    }
    rewind(fp);
    printf("open the file\n");
    head = ( stu *)malloc( sizeof( struct student));
    p = head;
    q = head;

    while ( fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%d",buf0, buf1, buf2, buf3, buf4, &m) != EOF) {
        if( p != head) {
            p = (stu *)malloc( sizeof( struct student));
            q->next = p;
            q = p;
        }
        n = strlen(buf0);
        buf0[n] = 0;
        if ( (p->name = (char *)malloc(n)) == NULL) {
            perror("fail to malloc");
            return NULL;
        }
        strncpy(p->name, buf0, n);
        n = strlen(buf1);
        buf1[n] = 0;
        if ( (p->school_year = (char *)malloc(n)) == NULL) {
            perror("fail to malloc");
            return NULL;
        }
        strncpy(p->school_year, buf1, n);

        n = strlen(buf2);
        buf2[n] = 0;
        if ( (p->academy = (char *)malloc(n)) == NULL) {
            perror("fail to malloc");
            return NULL;
        }
        strncpy(p->academy, buf2, n);

        n = strlen(buf3);
        buf3[n] = 0;
        if ( (p->profession = (char *)malloc(n)) == NULL) {
            perror("fail to malloc");
            return NULL;
        }
        strncpy(p->profession, buf3, n);

        n = strlen(buf4);
        buf4[n] = 0;
        if ( (p->class = (char *)malloc(n)) == NULL) {
            perror("fail to malloc");
            return NULL;
        }
        strncpy(p->class, buf4, n);
        p->score = m;
        p->next = NULL;
        printf("read %s successfully!\n", p->name);
        p = p->next;
    }

    fclose(fp);
    return head;
}

void stu_store(void)
{
    stu *p = head;
    FILE *fp = NULL;

    if (head == NULL) {
        printf("no student\n");
        return;
    }
    fp = fopen(STU_FILE, "w+");
    while (p != NULL) 
    {
        fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%d\n",p->name, p->school_year, p->academy, p->profession, p->class, p->score);
        p = p->next;
    }
    printf("stored successfully!\n");
    return ;
}



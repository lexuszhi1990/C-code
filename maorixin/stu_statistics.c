#include <stdio.h>
#include "common.h"

extern stu *head;
unsigned int stu_aver_point = 0;
unsigned int stu_total = 0;

void stu_statistics_get_point(void)
{
    stu *p = head;
    stu_aver_point = stu_total = 0;
    while (p != NULL){
        stu_aver_point += p->score;
        stu_total++;
        p = p->next;
    }
    stu_aver_point /=stu_total;
    return ;
}

void stu_statistics_point(void)
{
    stu_statistics_get_point();
    printf("the averange score is : %d\n", stu_aver_point);
    printf("the total num of student: %d\n", stu_total);

    return ;
}

void stu_statistics_num(void)
{
    int n = 0;
    stu *p = head;
    stu_statistics_get_point();
    printf("the student's name whose score above the average line\n");
    while (p != NULL) {
        if (p->score > stu_aver_point) {
            printf("%s\t score :%d\n", p->name, p->score);
            n++;
        }
        p = p->next;
    }
    printf("the num of students whose score above the average line : %d\n", n);

    return ; 
}

void stu_statistics_default(void)
{
    printf("sorry, not have this option, please try again\n");
}

stu *stu_statistics_search(stu *q)
{
    stu *p = head;
    stu *b = NULL;
    if (q == NULL) {
        q = p;
        while (p != NULL){
            if (p->score > q->score ) {
                q = p;
            }
            p = p->next;
        }
        return q;
    } else {
        b = NULL;
        while (p != NULL){
            if( p->score < q->score) {
                if (b == NULL) {
                    b = p;
                } else if (p->score > b->score) {
                    b = p;
                }
            }
            p = p->next;
        }

        return b;
    }

}

stu *stu_statistics_search_down(stu *q)
{
    stu *p = head;
    stu *b = NULL;
    if (q == NULL) {
        q = p;
        while (p != NULL){
            if (p->score < q->score ) {
                q = p;
            }
            p = p->next;
        }
        return q;
    } else {
        b = NULL;
        while (p != NULL){
            if( p->score > q->score) {
                if (b == NULL) {
                    b = p;
                } else if (p->score < b->score) {
                    b = p;
                }
            }
            p = p->next;
        }
        return b;
    }

}

void stu_statistics_rank_down(void)
{
    stu *q = NULL;
    stu *p = NULL;
    do {
        p = stu_statistics_search(q);
        if (p == NULL) {
            break;
        }
        q = p;
        printf("%-10s%-13s%-13s%-15s%-10s%-10s\n", "name : ", "shc_year : ", "academy : ", "profession : ", "class : ", "score : ");
        printf("%-10s%-13s%-13s%-15s%-10s%-10d\n",p->name, p->school_year, p->academy, p->profession, p->class, p->score);
    } while(1);

    return ;
}



void stu_statistics_rank_up(void)
{
    stu *q = NULL;
    stu *p = NULL;
    do {
        p = stu_statistics_search_down(q);
        if (p == NULL) {
            break;
        }
        q = p;
        printf("%-10s%-13s%-13s%-15s%-10s%-10s\n", "name : ", "shc_year : ", "academy : ", "profession : ", "class : ", "score : ");
        printf("%-10s%-13s%-13s%-15s%-10s%-10d\n",p->name, p->school_year, p->academy, p->profession, p->class, p->score);
    } while(1);

    return ;

}

void stu_statistics(void)
{
    int s = 0;
stu_statis:
    printf("statistics the student score : \n");
    printf("1 : output the averange point of the score and the total number \n");
    printf("2 : outout number of student whose score is great than average point\n");
    printf("3 : output the ranking name in down line\n");
    printf("4 : output the ranking name in up line\n");
    printf("0 : quit and back to the main menu\n");
    scanf("%d", &s);
    getchar();
    switch ( s) {
        case 0 : break ; 
        case 1 : stu_statistics_point();goto stu_statis;
        case 2 : stu_statistics_num();goto stu_statis;
        case 3 : stu_statistics_rank_down();goto stu_statis;
        case 4 : stu_statistics_rank_up();goto stu_statis;
        default :stu_statistics_default();goto stu_statis;
    }
    return ;

}




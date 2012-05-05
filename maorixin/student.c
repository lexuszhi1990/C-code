#include "common.h"
#include "stu_checkout.h"
#include "stu_statistics.h"
#include "stu_insert.h"
#include "stu_file.h"
#include "stu_input.h"
#include "stu_del_free.h"

stu *head = NULL;

void stu_quit(void)
{
    printf("quit ...\n");
}

void stu_default(void)
{
    printf("wrong number, please try again\n");
}

void stu_disp(stu *p)
{
    if (p == NULL) {
        perror("no this student");
        return ;
    }
    printf("%-10s%-13s%-13s%-15s%-10s%-10s\n", "name : ", "shc_year : ", "academy : ", "profession : ", "class : ", "score : ");
    printf("%-10s%-13s%-13s%-15s%-10s%-10d\n",p->name, p->school_year, p->academy, p->profession, p->class, p->score);
}

void meu_list(void)
{
    printf("This is main menu, please input a choice num  :\n");
    printf("1 : build  a student list\n");
    printf("2 : delete a student sorted by his name\n");
    printf("3 : checkout the student\n");
    printf("4 : insert a student into the list\n");
    printf("5 : statistics the student list\n");
    printf("8 : store student int to the file \n");
    printf("0 : quit\n");
}

int main(void)
{
    int choice = 1;
    head = stu_read();
    while(choice) {
        meu_list();
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 0 : stu_quit();break;
            case 1 : head = stu_import(head);break;
            case 2 : stu_del();break;
            case 3 : stu_checkout();break;
            case 4 : stu_insert();break;
            case 5 : stu_statistics();break;
            case 8 : stu_store();break;
            default : stu_default();break; 
        }
    }

    stu_clean();
    return 0;
}


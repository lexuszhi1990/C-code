#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct student *stu;
struct student
{
    int num;
    char name[20];
    stu next;
};
extern void store_stu(stu);
extern stu stu_malloc(stu);
extern void stu_check(FILE *);
extern int menu_list(void);
extern stu add_stu(stu);
extern void del_stu(stu);
extern void disp_stu(stu);


#endif

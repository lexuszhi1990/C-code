#ifndef COMMON_H_
#define COMMON_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student  stu;
struct student
{
    char *name;
    char *school_year;
    char *academy;
    char *profession;
    char *class;

    unsigned int score;
    stu *next;
};


void stu_disp(stu *);

#define BUF 1024


#endif

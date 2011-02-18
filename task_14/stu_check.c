#include <stdio.h>
#include <stdlib.h>
#include "main.h"
void stu_check(void * p)
{
    if (p == NULL) 
    {
        perror("error");
        exit(0);
    }
}

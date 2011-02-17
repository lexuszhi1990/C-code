#include <stdio.h>
#include <stdlib.h>
#include "main.h"
stu stu_malloc(stu p)
{
    if((p = malloc(sizeof(struct student))) == NULL)
        {
                perror("malloc fail");
                        exit(0);
        }
          return p;
}

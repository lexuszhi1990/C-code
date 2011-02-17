#include <stdio.h>
#include <stdlib.h>
#include "main.h"
void check(FILE *fp)
{
    if (fp == NULL) 
    {
        perror("error");
        exit(0);
    }
}

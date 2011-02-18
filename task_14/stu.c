#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, const char *argv[])
{
    int  stop = 0;
    int  choice = 0;
    stu head ;
    head = NULL;
    while( stop == 0)
    {
        choice = menu_list();
        switch( choice )
        {
            case  1  : head = add_stu(head);break;
            case  2  : head = del_stu(head);break;
            case  3  : disp_stu(head);break;
            case  4  : store_stu(head);break;
            case  5  : head = read_stu();break;
            case  9  : stop = 1;break;
            default  : break;
        }
    }
    return 0;
}

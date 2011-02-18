#include <stdio.h>

unsigned int total = 100;
unsigned int num = 3;
unsigned int counter = 1;

void del_arr(int i, int *arr)
{
    printf("num : %d out! %dth\n", arr[i-1], counter++);
    for ( i = i-1; i < total-1; i++) 
    {
        arr[i] = arr[i+1];
    }
    total--;
}


int main(int argc, const char *argv[])
{
    int i;
    int arr[total] ;
    for (i = 0; i < total; i++) 
    {
        arr[i] = i+1;
    }
    i = 1;
    while(total > 1)
    {
        printf("main: i:%d total %d\t", i, total);
        i = i+num-1;
        while (i > total) 
        {
            i = i - total;
        }
        del_arr(i ,arr);
    }
    printf("the only one survived :%d\n",arr[0]);
    return 0;
}

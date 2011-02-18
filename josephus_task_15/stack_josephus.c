#include <stdio.h>
int total = 10;
int counter = 3;
struct person {
    int num;
    struct preson *next;
};
typedef struct person *per;



pre init_link(int n)
{
    per p = NULL;
    if((p = malloc(sizeof(struct person))) == NULL)
    {
        perror("ess");
        exit(0);
    }
    p->num = 0;
    p->next = NULL;
    p = p->next;
    for (i = 1; i < n; i++) 
    {
        
    }
}

int main(int argc, const char *argv[])
{
    per head = NULL;
    head = init_link(total);
    print_link(head);
    head = del_link();
    return 0;
}

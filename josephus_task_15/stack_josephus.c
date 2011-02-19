#include <stdio.h>
#include <stdlib.h>
int total = 100;
int counter = 3;
typedef struct person *per;
struct person {
    int num;
    per next;
};

per init_link(int n, per p)
{
	int i;
    for (i = 1; i < n; i++) 
    {
    if((p->next = malloc(sizeof(struct person))) == NULL)
    {
        perror("ess");
        exit(0);
    }
    p->next->num = i;
    p->next->next = NULL;
    p = p->next;
    }
	return p;	     
}

void print_link(per p)
{
	per stop = p;
	printf("%-6d",p->num);
	p = p->next;
	while (p != stop) 
	{
		printf("%-6d",p->num);
		p = p->next;
	}
	putchar('\n');
}

void del_link(per p)
{
	per *pp = &p;
	int i = 1;
	while (*pp != (*pp)->next) 
	{
		if(i == 3)
		{
			i = 1;
			printf("%-6d ", (*pp)->num + 1);
			*pp = (*pp)->next;
		}
		pp = &(*pp)->next;				
		i++;
	}
	printf("\n%d survived\n", (*pp)->num + 1);
}

int main(int argc, const char *argv[])
{
	per head = malloc(sizeof(struct person));
	head->num = 0;
	per ss=  init_link(total, head);
	ss->next = head;
        print_link(head);
        del_link(head);
    return 0;
}

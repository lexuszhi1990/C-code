#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void *smalloc(size_t size)
{
	char *p;

	p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(p == MAP_FAILED)
		p = NULL;
	return (void *)p;
}

void sfree(void *ptr)
{
	
}

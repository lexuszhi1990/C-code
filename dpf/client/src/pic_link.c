#include "common.h"

static pic_t *pic_new_node(const char *filename)
{
	pic_t *p; int len;

	p = (pic_t *)malloc(sizeof(pic_t));
	if(p != NULL){
		len = strlen(filename);
		p->filename = (char *)malloc(len + 1);
		if(p->filename == NULL){
			free(p);
			return NULL;
		}
		strcpy(p->filename, filename);
		p->is_exsit = 1; p->need_renew = 1;
		p->next = NULL;
	}

	return p;
}

pic_t *pic_insert(pic_t **head, const char *filename)
{
	pic_t *p, *q;

	p = pic_new_node(filename);
	if(p == NULL)
		return NULL;
	if(*head == NULL){
		*head = p;
		return p;
	}
	q = *head;
	while(q->next != NULL)
		q = q->next;
	q->next = p;

	return p;
}

void pic_print(pic_t *head)
{
	pic_t *p;

	for(p = head; p != NULL; p = p->next)
		printf("file : %s\n", p->filename); 

	return ;
}

void pic_destroy(pic_t **head)
{
	pic_t *p, *q;

	if(*head == NULL)
		return ;
	for(p = *head; p != NULL; p = q){
		q = p->next;
		free(p);
	}

	return ;
}

int pic_get_num(pic_t *head)
{
	pic_t *p; int n;

	for(p = head, n = 0; p; p = p->next)
		n++;
	return n;
}

pic_t *pic_search(pic_t *head, const char *filename)
{
	pic_t *p;

	for(p = head; p != NULL; p = p->next)
		if(strcmp(p->filename, filename) == 0)
			break;
	return p;
}

int adjust(pic_t **head, func_t handler)
{
	pic_t *p, *q;
	int need_renew = 0;
	char path[1024];

	if(*head == NULL)
		return need_renew;

	p = *head;
	if((*head)->is_exsit == 0){
		*head = (*head)->next;
		free(p);
		need_renew = 1;
	}
	if(*head == NULL)
		return need_renew;

	q = p; p = p->next;
	while(p != NULL){
		if(p->is_exsit == 0){
			q->next = p->next;
			if(handler != NULL){
				sprintf(path, "%s/%s", JPG_PATH, p->filename);
				handler(path);
			}
			free(p); p = q->next;
			need_renew = 1;
			continue;
		}
		p->is_exsit = 0;
		p = p->next; q = q->next;
	}

	return need_renew;
}

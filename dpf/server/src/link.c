#include "common.h"

static node_t *new_node(int id, const struct sockaddr_in *addr) 
{
	node_t *p;

	p = (node_t *)malloc(sizeof(node_t));
	if(p != NULL){
		p->id = id;
		memcpy(&p->addr, addr, sizeof(struct sockaddr_in));
		p->next = NULL;
	}
	
	return p;
}

node_t *insert(node_t **head, int id, const struct sockaddr_in *addr)
{	
	node_t *p;

	p = new_node(id, addr);
	if(p == NULL) return NULL;

	if(*head == NULL){
		*head = p;
	}else{
		node_t *q;

		for(q = *head; q->next != NULL; q = q->next);
		q->next = p;
	}
	
	return p;
}

void print(node_t *head)
{
	node_t *p; char buf[IP_LEN];
	
	for(p = head; p != NULL; p = p->next)
		printf("id: %d, port: %u, ip: %s\n", 
			p->id, htons(p->addr.sin_port), 
			inet_ntop(AF_INET, &p->addr.sin_addr.s_addr, buf, sizeof(buf)));
}

void destroy(node_t **head)
{
	node_t *p, *q;

	for(p = *head; p != NULL; p = q){
		q = p->next;
		free(p);
	}

	*head = NULL;
}

node_t *search_by_id(node_t *head, int id)
{
	node_t *p;

	for(p = head; p != NULL; p = p->next)
		if(p->id == id)
			break;

	return p;
}

node_t *search_by_ip(node_t *head, const char *ip)
{	
	in_addr_t addr; node_t *p;

	inet_pton(AF_INET, ip, &addr);
	for(p = head; p != NULL; p = p->next)
		if(p->addr.sin_addr.s_addr == addr)
			break;

	return p;
}

node_t *delete_by_id(node_t **head, int id)
{
	node_t *p, *q;

	if(*head == NULL)
		return NULL;
	
	if((*head)->id == id){
		p = *head;
		*head = (*head)->next;
		
		return p;
	}

	for(p = *head, q = p->next; q != NULL; q = q->next){
		if(q->id == id){
			p->next = q->next;
			q->next = NULL;

			return q;
		}	

		p = p->next;
	}

	return q;
}

inline static int cmp_addr(const struct sockaddr_in *p, 
			const struct sockaddr_in *q)
{
	return p->sin_family == q->sin_family &&
			p->sin_port == q->sin_port &&
			p->sin_addr.s_addr == q->sin_addr.s_addr; 
}

node_t *delete_by_addr(node_t **head, const struct sockaddr_in *addr)
{
	node_t *p, *q;

	if(*head == NULL)
		return NULL;
	
	if(cmp_addr(&(*head)->addr, addr)){
		p = *head;
		*head = (*head)->next;
		
		return p;
	}

	for(p = *head, q = p->next; q != NULL; q = q->next){
		if(cmp_addr(&(*head)->addr, addr)){
			p->next = q->next;
			q->next = NULL;

			return q;
		}	

		p = p->next;
	}

	return q;
}

int get_count(node_t *head)
{
   	node_t *p; int n;
 
	n = 0;
	for(p = head; p != NULL; p = p->next)
		n++;
	return n;
}

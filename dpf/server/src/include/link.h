#ifndef LINK_H_
#define LINK_H_

#define IP_LEN 16

typedef struct node node_t; 
struct node 
{
	int id;
	struct sockaddr_in addr;
	node_t *next;
};

extern node_t *insert(node_t **head, int id, const struct sockaddr_in *addr);
extern void print(node_t *head);
extern void destroy(node_t **head);
extern node_t *search_by_id(node_t *head, int id);
extern node_t *search_by_ip(node_t *head, const char *ip);
extern node_t *delete_by_id(node_t **head, int id);
extern node_t *delete_by_addr(node_t **head, const struct sockaddr_in *addr);
extern int get_count(node_t *head);

#endif

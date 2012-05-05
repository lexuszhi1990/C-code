#ifndef PIC_LINK_H_
#define PIC_LINK_H_

typedef struct pic_node pic_t;
struct pic_node
{
	char *filename;
	int is_exsit;
	int need_renew;
	pic_t *next;
};

extern pic_t *pic_insert(pic_t **head, const char *filename);
extern void pic_print(pic_t *head);
extern int pic_get_num(pic_t *head);
extern pic_t *pic_search(pic_t *head, const char *filename);
extern int adjust(pic_t **head);
extern void pic_destroy(pic_t **head);

#endif

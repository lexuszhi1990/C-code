#ifndef PIC_LINK_H_
#define PIC_LINK_H_

#include "types.h"

extern pic_t *pic_insert(pic_t **head, const char *filename);
extern void pic_print(pic_t *head);
extern int pic_get_num(pic_t *head);
extern pic_t *pic_search(pic_t *head, const char *filename);
extern int adjust(pic_t **head, func_t handler);
extern void pic_destroy(pic_t **head);

#endif

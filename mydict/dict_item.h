#ifndef DICT_ITEM_H_
#define DICT_ITEM_H_

#include <string.h>

typedef struct
{
	char *key_word;
	char **trans;
	int trans_num;
}ditem_t;

extern int set_dict_item(ditem_t *item, const char *key_word, const char *trans_line);
extern char *get_key_word(const ditem_t *item);
extern void free_item(ditem_t *item);

#endif

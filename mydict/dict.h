#ifndef DICT_H_
#define DICT_H_

typedef struct node dict_t;
struct node
{
	ditem_t *dict;
	int nword;
	dict_t *usr;
};

extern dict_t *dict_init_txt(const char *filename, dict_t *d);
extern ditem_t *dict_search(const char *key, const dict_t *d);
extern void dict_free(dict_t *d);

#endif

#include "common.h"

int set_trans(ditem_t *item, const char *trans_line)
{
	int i, ntrans, l; 
	const char *p, *q;

	p = trans_line; ntrans = 1;
	while(*p != '\0'){	
		if(*p == '@')
			ntrans++;
		p++;
	}

	item->trans_num = ntrans;
	item->trans = (char **)malloc(sizeof(char *) * ntrans);
	if(item->trans == NULL)
		return FALSE;
	
	i = 0; q = p = trans_line; 
	while(1){
		if(*p == '@' || *p == '\0'){
			l = p - q;
			item->trans[i] = (char *)malloc(sizeof(char) * (l + 1));
			if(item->trans[i] == NULL)
				return FALSE;
			strncpy(item->trans[i], q, l);
			*(item->trans[i] + l) = '\0';
			i++; q = p + 1;

			if(*p == '\0')
				break;
		}
		p++;
	}

	return TRUE;
}

int set_key_word(ditem_t *item, const char *key)
{
	int len;

	len = strlen(key);
	if(item->key_word != NULL) 
		free(item->key_word);

	item->key_word = (char *)malloc(sizeof(char) * (len + 1));
	if(item == NULL)
		return FALSE;
	strcpy(item->key_word, key);

	return TRUE;
}

int set_dict_item(ditem_t *item, const char *key_word, const char *trans_line)
{
	if(key_word == NULL || trans_line == NULL)
		return FALSE;

	return set_key_word(item, key_word)
		&& set_trans(item, trans_line);
}

char *get_key_word(const ditem_t *item)
{
	char *p; int len;

	if(item->key_word == NULL)
		return NULL;
	len = strlen(item->key_word);
	p = (char *)malloc(sizeof(char) * (len + 1));
	
	return p;
}

void free_item(ditem_t *item)
{
	int i;
	
	if(item->key_word != NULL)
		free(item->key_word);
	if(item->trans != NULL){
		for(i = 0; i < item->trans_num; i++)
			if(item->trans[i] != NULL)
				free(item->trans[i]);
		free(item->trans);
		item->trans = NULL;
		item->trans_num = 0;
	}
}

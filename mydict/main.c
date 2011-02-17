#include "common.h"

int main(void)
{
	dict_t dict; ditem_t *item;
	char buf[BUF_SIZE]; int i;

	if(dict_init_txt("dict.txt", &dict) == NULL)
		err_sys("fail to dict_init");
	DEBUG_PRINT0("init done...\n");

	while(fgets(buf, BUF_SIZE, stdin)){
		if(buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		if(strcmp(buf, "exit") == 0)
			break;
		item = dict_search(buf, &dict);
		
		if(item == NULL)
			printf("not found...\n");
		else{
			printf("%s :\n", item->key_word);
			for(i = 0; i < item->trans_num; i++)
				printf("trans %d: %s\n", i + 1, item->trans[i]);
		}
		printf("\n");
	}

	dict_free(&dict);

	return 0;
}	

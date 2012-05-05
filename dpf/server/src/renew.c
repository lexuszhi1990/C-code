#include "common.h"

time_t rt;
pic_t *pic_head = NULL;

int init_renew(const char *path)
{
	DIR *dp; int res = 0;
	struct dirent *item; 

	dp = opendir(path);
	if(dp == NULL)
		return -1;
	while(item = readdir(dp)){
		if(item->d_name[0] == '.')
			continue;
		if(pic_insert(&pic_head, 
			item->d_name) == NULL){
			res = -1;	
			break;
		}
	}
	
	rt = time(NULL);
	if(res == -1)
		pic_destroy(&pic_head);
	closedir(dp);

#ifdef DEBUG
	pic_print(pic_head);
#endif

	return res;
}

int need_renew(const char *path)
{
	DIR *dp; pic_t *p, *res;
	struct dirent *item;
	struct stat statbuf;
	int is_need = 0;
	char apath[BUF_SIZE];

	dp = opendir(path);
	if(dp == NULL)
		return -1;
	
	for(p = pic_head; p != NULL; p = p->next){
		p->need_renew = 0; p->is_exsit = 0;
	}
	
	while(item = readdir(dp)){
		if(item->d_name[0] == '.')
			continue;
		p = pic_search(pic_head, item->d_name);
		if(p == NULL){
			res = pic_insert(&pic_head, item->d_name);
			if(res == NULL)
				err_delay("fail to pic_insert");
			else
				is_need = 1;
		}else{
			p->is_exsit = 1;
			sprintf(apath, "%s/%s", path, item->d_name);
			stat(apath, &statbuf);
			if(statbuf.st_mtim.tv_sec > rt){
				/* debug info */
				//printf("pic : %u, cur : %u\n", statbuf.st_mtim.tv_sec, rt);
				p->need_renew = 1;
				is_need = 1;
			}
		}
	}
	closedir(dp);
	
	rt = time(NULL); /* fresh renew_time */
	is_need |= adjust(&pic_head);

	return is_need;
}

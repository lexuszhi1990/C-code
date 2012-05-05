#include "common.h"

/* request format : get filename first|not */
char *parse_request(char *request, int *is_first)
{
	char *p, *q;

	p = strstr(request, " ");
	q = strstr(p + 1, " ");
	if(strcmp(q + 1, "first") == 0)
		*is_first = 1;
	else
		is_first = 0;
	*q = '\0';

	return p + 1;
}

int trans_file(const char *filename, int cfd, int is_first)
{
	int fd, nread; 
	char buf[BUF_SIZE], apath[BUF_SIZE];
	pic_t *p;

	if(strcmp(filename, "index.xml") == 0){ /* get picture list */
		for(p = pic_head; p != NULL; p = p->next){
			if(is_first || p->need_renew == 1){
				write(cfd, p->filename, strlen(p->filename));
				write(cfd, "@", sizeof(char));
			}
		}
	}else{
		sprintf(apath, "%s/%s", ROOT_PATH, filename);
		fd = open(apath, O_RDONLY);
		if(fd == -1){
			write(cfd, "err", 3);
		}else{
			while(nread = read(fd, buf, BUF_SIZE))
				write(cfd, buf, nread);
			close(fd);
		}
	}

	return 0;
}

#include "common.h"

char *append = NULL;

char *get_append(char *buf)
{
	char *p;	
		
	p = strstr(buf, " ");
	*p = '\0';
	if(strcmp(buf, "first") == 0)
		return "first";
	else
		return "";
}

char *get_file_list(const struct sockaddr_in *tcp_addr, char *buf)
{
	int tfd, n; char cmd[CMD_LEN];
	static char backup[BUF_SIZE];	

	if(buf == NULL)
		buf = backup;

	tfd = tcp_sock_init(tcp_addr);
	if(tfd == -1)
		return NULL;
	sprintf(cmd, "get index.xml %s", append);
	write(tfd, cmd, strlen(cmd));
		
	sleep(1); /* make sure data reach on time */
		
	n = read(tfd, buf, BUF_SIZE);
	buf[n] = '\0';
	close(tfd);

	return buf;
}

int get_file(int tfd, const char *file_name)
{
	char cmd[CMD_LEN]; int fd, n;	
	char path[BUF_SIZE]; pic_t *pic;
	char file_buf[BUF_SIZE];

	sprintf(cmd, "get %s %s", file_name, append);
	write(tfd, cmd, strlen(cmd));

	sprintf(path, "%s/%s", JPG_PATH, file_name);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
		return -1;
	while(n = read(tfd, file_buf, BUF_SIZE))
		write(fd, file_buf, n);
	close(tfd);

	pic = pic_search(pic_head, file_name);
	if(pic == NULL)
		pic_insert(&pic_head, file_name);
	else 
		pic->is_exsit = 1;

	return 0;
}

int renew_file(const struct sockaddr_in *tcp_addr, char *buf)
{
	int tfd, fd; 
	int i, s, res;
	pic_t *pic;

	for(pic = pic_head; pic != NULL; pic = pic->next)
		pic->is_exsit = 0;
	i = 0; s = 0;

	while(buf[i] != '\0'){
		if(buf[i] == '@'){
			buf[i] = '\0';

			tfd = tcp_sock_init(tcp_addr);
			if(tfd == -1)
				return -1;

			res = get_file(tfd, &buf[s]);
			close(tfd);
			if(res == -1)
				return -1;	
			
			s = i + 1;	
		}			
		i++;
	}
	adjust(&pic_head, unlink);

	return 0;
}

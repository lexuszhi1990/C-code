#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define SERV_PORT 8000
#define SERV_IP "192.168.0.5"
#define QLEN 20

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

void err_usr(const char *str)
{
	fputs(str, stderr);
	exit(2);
}

int main(void)
{
	int lfd, res; struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		err_sys("fail to socket");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	res = bind(lfd, (struct sockaddr *)&serv_addr, 
			sizeof(serv_addr));
	if(res == -1)
		err_sys("fail to bind");	
	res = listen(lfd, QLEN);
	if(res == -1)
		err_sys("fail to listen");

	int client[1024]; int max_i, i;
	int efd; struct epoll_event tep, ep[1024];

	for(i = 0; i < 1024; i++)
		client[i] = -1;	
	max_i = -1;
	efd = epoll_create(1024);
	if(efd == -1)
		err_sys("fail to epoll_create");
	tep.events = EPOLLIN; tep.data.fd = lfd;
	res = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &tep);
	if(res == -1)
		err_sys("fail tl epoll_ctl");

	while(1){
		int nread, i, j, cfd;

		nread = epoll_wait(efd, ep, 1024, -1);
		if(nread == -1)
			err_sys("fail to epoll_wait");
		for(i = 0; i < nread; i++){
			if(!(ep[i].events & EPOLLIN))
				continue;
			if(ep[i].data.fd == lfd){
				cfd = accept(lfd, NULL, NULL);
				if(cfd == -1)
					err_sys("fail to accept");
				for(j = 0; j < 1024; j++)
					if(client[j] == -1){
						client[j] = cfd;
						break;
					}
				if(j == 1024)
					err_usr("too many clients...\n");
				if(j > max_i) max_i = j;
				tep.events = EPOLLIN; tep.data.fd = cfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &tep);
				if(res == -1)
					err_sys("fail to epoll_ctl");
			}else{
				int n; char buf[1024];

				cfd = ep[i].data.fd;
				n = read(cfd, buf, 1024);
				if(n == 0){
					for(j = 0; j <= max_i; j++)
						if(client[j] == cfd){
							client[j] = -1;
							break;
						}
					if(j > max_i)
						printf("the client not exsit...\n");
					res = epoll_ctl(efd, EPOLL_CTL_DEL, cfd, NULL);
					if(res == -1)
						err_sys("fail to epoll_ctl");
					close(cfd);
				}else{
					for(j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
					write(cfd, buf, n);
				}
			}
							
			printf("one socket is over...\n");
		}
		
		printf("one round is over...\n");
	}
	
	close(lfd);
	close(efd);
	printf("bye-bye...\n");

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 8000
#define SERV_IP "192.168.0.5"

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

int main(void)
{
	int sfd, res, n; char buf[1024]; 
	struct sockaddr_in cli_addr, serv_addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
		err_sys("fail to socket");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	res = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(res == -1)
		err_sys("fail to connect");
	
	while(1){
		n = read(STDIN_FILENO, buf, 1024);
		if(!strncmp(buf, "exit", 4))
			break;
		write(sfd, buf, n);
		n = read(sfd, buf, 1024);	
		write(STDOUT_FILENO, buf, n);
	}
	close(sfd);

	return 0;
}

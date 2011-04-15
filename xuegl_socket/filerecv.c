#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int clifd;
	int ret;
	char buf[1024];
	int file;
	int recvlen;
	char filename[256];
	int filenamelen;
	int filelen;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("192.168.0.5");

	clifd = socket(AF_INET, SOCK_STREAM, 0);
	ret = connect(clifd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret != 0)
	{
		perror("connect error\n");
	}
	
while(1)
{
	recvlen = recv(clifd, buf, sizeof(buf), 0);
	if(strcmp(buf, "##end##") == 0)
	{
		printf("end\n");
		break;
	}
	strcpy(filename, buf);
	printf("begin file %s\n", buf);

	strcat(filename, ".recv");
	file = open(filename, O_CREAT | O_RDWR, 0644);
	if(file < 0)
	{
		perror("file create error\n");
		return 0;
	}

	filenamelen = strlen(buf);
//	filelen = *((int*)(buf+filenamelen+1));
	filelen = atoi(buf+filenamelen+1);	
	printf("filelen=%d\n", filelen);
	write(file, buf+filenamelen+5, recvlen-filenamelen-5);
	filelen -= (recvlen - filenamelen - 5);

	while(1)
	{
		if(filelen < sizeof(buf))
			recvlen = recv(clifd, buf, filelen, 0);
		else
			recvlen = recv(clifd, buf, sizeof(buf), 0);

		write(file, buf, recvlen);
		filelen -= recvlen;
		if(filelen == 0)
			break;
	}
	close(file);
	printf("end file\n");
}
	close(clifd);
}

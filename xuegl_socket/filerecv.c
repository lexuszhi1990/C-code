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
	char* p;

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
	recvlen = recv(clifd, &filenamelen, sizeof(int), 0);
	printf("filenamelen = %d\n", filenamelen);
	if(filenamelen == 0xffffffff)
		break;
	recvlen = recv(clifd, filename, filenamelen, 0);

// /home/akaedu/send/...   /home/akaedu/recv/....
	p = strstr(filename, "/send/");
	p++;
	memcpy(p, "recv", 4);
	printf("filename=%s\n", filename);
	recvlen = recv(clifd, &filelen, sizeof(int), 0);
	
	file = open(filename, O_CREAT | O_RDWR, 0644);
	if(file < 0)
	{
		perror("file create error\n");
		return 0;
	}

	printf("filelen=%d\n", filelen);

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

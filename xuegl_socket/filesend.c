#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char* files[1024];
int count = 0;


void dosend(int fd, int index)
{
	char* filename = files[index];
	char buf[1024];
	int file = open(filename, O_RDONLY);
	struct stat buf_stat;
	int ret;
	int readsize;
	int sendsize;
	int filesize;
	char tmp[32];
	int filenamelen = strlen(filename)+1;
	
	send(fd, &filenamelen, sizeof(int), 0);
	send(fd, filename, strlen(filename)+1, 0);

	// get filelen
	fstat(file, &buf_stat);
	printf("sizeof(buf_stat.st_size) =%d, filelen=%d\n", 
			sizeof(buf_stat.st_size), (int)buf_stat.st_size);
	filesize = buf_stat.st_size;
	send(fd, &filesize, sizeof(filesize), 0);
	
	while(1)
	{
		readsize = read(file, buf, sizeof(buf));
		if(readsize == 0)
			break;
		sendsize = 0;
		while(sendsize != readsize)
		{
			ret = send(fd, buf+sendsize, readsize-sendsize, 0);
			if(ret < 0)
			{
				perror("send failure\n");
				return;
			}
			sendsize += ret;
		}
	}

	close(file);
}

void* send_file(void* p)
{
	int fd = (int)p;
	int index = 0;
	for(index = 0; index < count; index++)
	{
		dosend(fd, index);
	}

	// send file end;
	index = 0xffffffff;
	send(fd, &index, 4, 0);
	recv(fd, &index, sizeof(index), 0);
	close(fd);
}

void getfiles()
{
	char* path = "/home/akaedu/send";
	char* filename;
	DIR* dir = opendir(path);
	struct dirent* entry;
	while((entry = readdir(dir)) != NULL)
	{
		if(*entry->d_name == '.')
			continue;

		filename = malloc(256);
		strcpy(filename, path);
		strcat(filename, "/");
		strcat(filename, entry->d_name);
		
		files[count++] = filename;
	}
}

int main(int argc, char* argv[])
{
	int sockfd;
	char buf[1024];
	int ret = 0;
	fd_set sock_set;
	struct timeval tv;
	int max_fd = -1;

	int clientfd;
	int cc = 0;
	int i;
	pthread_t t_id;

	getfiles();

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("192.168.0.5");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret != 0)
	{
		perror("bind error\n");
		return 1;
	}	
	ret = listen(sockfd, 5);
	
	while(1)
	{
		FD_ZERO(&sock_set);
		FD_SET(sockfd, &sock_set);
		if(max_fd < sockfd) max_fd = sockfd;
		static int timegap = 0;
		tv.tv_sec = timegap++;
		tv.tv_usec = 0;
		ret = select(max_fd+1, &sock_set, 0, 0, &tv);
		if(ret == -1)
		{
			// select error;
		}
		else if(ret == 0)
		{	
			printf("no message\n");			
			// no socket message
		}
		else // ret > 0
		{
			if(FD_ISSET(sockfd, &sock_set))
			{
				clientfd = accept(sockfd, 0, 0);
				pthread_create(&t_id, NULL, send_file, (void*)clientfd);
			}
		}
	}
}


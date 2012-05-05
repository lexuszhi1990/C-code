#include "common.h"

int init_udp_sock(in_port_t port, const char *ip)
{
	int sfd, res;
	struct sockaddr_in udp_serv_addr;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		return -1;

	memset(&udp_serv_addr, 0, sizeof(udp_serv_addr));
	udp_serv_addr.sin_family = AF_INET;
	udp_serv_addr.sin_port = htons(port);	
	inet_pton(AF_INET, ip, &udp_serv_addr.sin_addr.s_addr);

	res = bind(sfd, (struct sockaddr *)&udp_serv_addr, sizeof(udp_serv_addr));
	if(res == -1){
		close(sfd);
		return -1;
	}

	return sfd;
}

int init_tcp_sock(in_port_t port, const char *ip)
{
	int lfd, res;
	struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		return -1;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(TCP_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	res = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(res == -1){
		close(lfd);
		return -1;
	}

	res = listen(lfd, QLEN);
	if(res == -1){
		close(lfd);
		return -1;
	}

	return lfd;
}

void *make_shared_mem(size_t size)
{
	void *p;

	p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
	memset(p, 0, size);

	return p;
}


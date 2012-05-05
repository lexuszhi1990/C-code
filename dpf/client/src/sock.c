#include "common.h"

int udp_sock_init(const char *serv_ip, in_port_t udp_port, struct sockaddr_in *serv_addr)
{
	int sfd, n;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		return -1;
	
	memset(serv_addr, 0, sizeof(*serv_addr));
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(udp_port);
	inet_pton(AF_INET, serv_ip, &(serv_addr->sin_addr.s_addr));

	n = sendto(sfd, "syn", 3, 0, (struct sockaddr *)serv_addr, sizeof(*serv_addr));
	if(n == -1){
		close(sfd);
		return -1;
	}

	return sfd;
}

int udp_sock_destroy(int sfd, const struct sockaddr_in *serv_addr)
{
	int n;

	n = sendto(sfd, "fin", 3, 0, (struct sockaddr *)serv_addr, sizeof(*serv_addr));
	close(sfd);

	return 0;
}

int tcp_sock_init(const struct sockaddr_in *tcp_addr)
{
	int tfd, res;	

	tfd = socket(AF_INET, SOCK_STREAM, 0);
	if(tfd == -1)
		return -1;
	res = connect(tfd, (struct sockaddr *)tcp_addr, sizeof(*tcp_addr));
	if(res == -1){
		close(tfd);
		return -1;
	}
	return tfd;
}

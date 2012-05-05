#ifndef SOCK_H_
#define SOCK_H_

#define TCP_PORT 8000
#define UDP_PORT 8080
#define SERV_IP "192.168.0.26"

extern int udp_sock_init(const char *serv_ip, in_port_t udp_port, 
		struct sockaddr_in *serv_addr);
extern int udp_sock_destroy(int sfd, const struct sockaddr_in *serv_addr);
extern int tcp_sock_init(const struct sockaddr_in *tcp_addr);

#endif

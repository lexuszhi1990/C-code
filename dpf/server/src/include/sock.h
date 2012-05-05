#ifndef SOCK_H_
#define SOCK_H_

extern int init_udp_sock(in_port_t port, const char *ip);
extern int init_tcp_sock(in_port_t port, const char *ip);

#endif 

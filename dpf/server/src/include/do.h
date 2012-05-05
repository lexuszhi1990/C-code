#ifndef DO_H_
#define DO_H_

typedef struct
{
	char *serv_ip;
	in_port_t port;
}arg_t;
typedef void *(*tfn_t)(void *);

extern tfn_t handler[];

extern void *do_renew(void *arg);
extern void *do_reg(void *arg);
extern void *do_trans(void *arg);

#endif

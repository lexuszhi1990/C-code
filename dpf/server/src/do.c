#include "common.h"

tfn_t handler[TH_NUM] = {do_reg, do_renew, do_trans};

void *do_renew(void *arg)
{
	int sfd; int res, n;
	arg_t *rarg; node_t *p;

	rarg = (arg_t *)arg;
	
	sfd = init_udp_sock(rarg->port, rarg->serv_ip);
	if(sfd == -1)
		return (void *)-1;
	res = init_renew(ROOT_PATH);
	if(res == -1)
		return (void *)-1;

	while(1){
		sleep(SEC);
		
		res = need_renew(ROOT_PATH);
		if(res == -1)
			err_delay("error occurs while renewing");
		else if(res > 0){
			p = client;
			while(p != NULL){
				n = sendto(sfd, RENEW_MSG, strlen(RENEW_MSG), 0, (struct sockaddr *)&(p->addr), sizeof(p->addr));
				/* get reply */
				p = p->next;
			}
		}
		/* debug infomation */
		pic_print(pic_head);
	}
	close(sfd);

	return NULL;
}

void *do_reg(void *arg)
{
	int sfd, nread, id, n;
	node_t *p; socklen_t len;
	char buf[BUF_SIZE];
	struct sockaddr_in udp_cli_addr;		
	arg_t *rarg;

	rarg = (arg_t *)arg;
	sfd = init_udp_sock(rarg->port, rarg->serv_ip);
	if(sfd == -1)
		return (void *)-1;		
	
	while(1){
		len = sizeof(udp_cli_addr);
		nread = recvfrom(sfd, buf, BUF_SIZE, 0, 
				(struct sockaddr *)&udp_cli_addr, &len);
		if(strncmp(buf, "syn", 3) == 0){
			id = (int)time(NULL);
			p = insert(&client, id, &udp_cli_addr);
			if(p == NULL)
				err_delay("fail to insert");
			n = sendto(sfd, FIRST_MSG, strlen(FIRST_MSG), 0, (struct sockaddr *)&p->addr, sizeof(p->addr));
		}else if(strncmp(buf, "fin", 3) == 0){
			p = delete_by_addr(&client, &udp_cli_addr);
			if(p != NULL)
				free(p);
		}
#ifdef DEBUG		
		print(client); /* for debuging... */
#endif
	}
	close(sfd);
	
	return NULL;
}

void *do_trans(void *arg)
{
	int lfd, cfd, nread, is_first;
	arg_t *rarg;
	struct sockaddr_in cli_addr; socklen_t len; 
	char buf[BUF_SIZE], *filename;

	rarg = (arg_t *)arg;
	lfd = init_tcp_sock(rarg->port, rarg->serv_ip);
	if(lfd == -1)
		return (void *)-1;

	while(1){
		len = sizeof(cli_addr);
		cfd = accept(lfd, (struct sockaddr *)&cli_addr, &len);
		if(cfd == -1)
			return (void *)-1;
		
		nread = read(cfd, buf, BUF_SIZE);
		filename = parse_request(buf, &is_first);
		trans_file(filename, cfd, is_first);
		
		close(cfd);			
	}	
	close(lfd);

	return NULL;
}

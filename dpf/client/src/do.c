#include "common.h"

pic_t *pic_head = NULL;

pthread_rwlock_t rwlock;
sem_t sem;

void *do_renew(void *arg)
{
	int sfd, tfd, fd; int n, res;
	struct sockaddr_in serv_addr, tcp_addr;
	char buf[BUF_SIZE];

	sfd = udp_sock_init(SERV_IP, UDP_PORT, &serv_addr);
	if(sfd == -1)
		return (void *)-1;

	memset(&tcp_addr, 0, sizeof(tcp_addr));
	tcp_addr.sin_family = AF_INET;
	tcp_addr.sin_port = htons(TCP_PORT);
	inet_pton(AF_INET, SERV_IP, &tcp_addr.sin_addr.s_addr);

	while(1){
		/* block, until it need to renew picture */
		n = recvfrom(sfd, buf, BUF_SIZE, 0, NULL, NULL);
		if(n == -1)
			err_sys("fail to recvfrom");
		buf[n] = '\0';
		
		append = get_append(buf);	
		if(get_file_list(&tcp_addr, buf) == NULL)
			return (void *)-1;

		/* reach shared area */
		pthread_rwlock_wrlock(&rwlock);
		res = renew_file(&tcp_addr, buf);
		if(res == -1)
			return (void *)-1;
		pthread_rwlock_unlock(&rwlock);
	}
	udp_sock_destroy(sfd, &serv_addr);

	return NULL;
}

void *do_mouse(void *arg)
{
	fb_info_t *fb = (fb_info_t *)arg;	
	int fd; char buf[8];
	mouse_event_t me;
	int mx = fb->x_res / 2, my = fb->y_res / 2, n;

	fd = mouse_open(NULL);
	while(1){
		cursor_draw(fb, mx, my);
		
		n = read(fd, buf, 8);
		mouse_parse(buf, &me);
		
		cursor_restore(fb, mx, my);
		mx += me.x, my += me.y;
		if(me.button == 1)
			sem_post(&sem);
	}

	return NULL;
}

void *do_dispjpg(void *arg)
{
	fb_info_t *fb = (fb_info_t *)arg;
	int i = 0, j, res; char path[1024];
	struct timespec tspec; 
	pic_t *p;

tryagain:
	p = pic_head;
	if(p == NULL){
	    sleep(1);
	    goto tryagain;
	}

	tspec.tv_sec = time(NULL) + 5; tspec.tv_nsec = 0;
	while(1){
		j = rand() % HAND_NUM;		

		sprintf(path, "%s/%s", JPG_PATH, p->filename);
		res = sem_timedwait(&sem, &tspec);
		if(res == -1){
		    if(errno != ETIMEDOUT)
			return (void *)-1;
		}

		pthread_rwlock_rdlock(&rwlock);
		handler[j](path, *fb);
		pthread_rwlock_unlock(&rwlock);
		p = p->next;
		if(p == NULL)
		    p = pic_head;
		tspec.tv_sec = time(NULL) + 5;
	}

	return NULL;
}


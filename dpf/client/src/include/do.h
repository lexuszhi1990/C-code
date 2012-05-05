#ifndef DO_H_
#define DO_H_

#define BUF_SIZE 1024
#define CMD_LEN 1024
#define JPG_PATH "../jpg"

extern pic_t *pic_head;
extern pthread_rwlock_t rwlock;
extern sem_t sem;

extern void *do_renew(void *arg);
extern void *do_mouse(void *arg);
extern void *do_dispjpg(void *arg);

#endif


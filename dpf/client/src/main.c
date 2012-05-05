#include "common.h"

int main(int argc, char *argv[])
{
	fb_info_t fb; 
	pthread_t tid[3]; int i;

	if(fb_init(NULL, &fb) == NULL)
		err_sys("fail to fb_init");
	sem_init(&sem, 0, 1);
	pthread_rwlock_init(&rwlock, NULL);

	pthread_create(&tid[0], NULL, do_renew, NULL);
	pthread_create(&tid[1], NULL, do_dispjpg, (void *)&fb);
	pthread_create(&tid[2], NULL, do_mouse, (void *)&fb);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	fb_destroy(&fb);
	pic_destroy(&pic_head);
	sem_destroy(&sem);
	pthread_rwlock_destroy(&rwlock);

	return 0;
}

#include "common.h"

void err_thread(const char *str, int err)
{
	char msg[BUF_SIZE];
	
	sprintf(msg, "%s : %s\n", str, strerror(err));
	fputs(msg, stderr);

	pthread_exit((void *)3);
}

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

void err_usr(const char *str)
{
	fputs(str, stderr);
	exit(2);
}

void err_delay(const char *str)
{
	perror(str);
	sleep(DELAY_SEC);
}

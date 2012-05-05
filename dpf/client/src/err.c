#include "common.h"

void err_sys(const char *str)
{
	perror(str);
	exit(ESYS);
}

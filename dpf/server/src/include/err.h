#ifndef ERR_H_
#define ERR_H_

#define DELAY_SEC 5

extern void err_sys(const char *str);
extern void err_usr(const char *str);
extern void err_delay(const char *str);
extern void err_thread(const char *str, int err);

#endif

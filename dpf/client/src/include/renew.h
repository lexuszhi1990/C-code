#ifndef RENEW_H_
#define RENEW_H_

extern char *append;

extern char *get_append(char *buf);
extern char *get_file_list(const struct sockaddr_in *tcp_addr, char *buf);
extern int get_file(int tfd, const char *file_name);
extern int renew_file(const struct sockaddr_in *tcp_addr, char *buf);

#endif

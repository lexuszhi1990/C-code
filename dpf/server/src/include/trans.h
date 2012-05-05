#ifndef TRANS_H_
#define TRANS_H_

extern char *parse_request(char *request, int *is_first);
extern int trans_file(const char *filename, int cfd, int is_first);

#endif

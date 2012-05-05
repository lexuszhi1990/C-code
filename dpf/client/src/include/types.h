#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned int u32_t;
typedef unsigned short u16_t;
typedef unsigned char u8_t;

typedef struct
{
	int x_res;
	int y_res;
	int bpp;
	char *fb_buf;
}fb_info_t;
typedef int (*handler_t)(const char *, fb_info_t);

typedef struct pic_node pic_t;
struct pic_node
{
	char *filename;
	int is_exsit;
	int need_renew;
	pic_t *next;
};
typedef int (*func_t)(const char *);

#endif

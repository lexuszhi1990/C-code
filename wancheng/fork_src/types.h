#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned int u32_t;
typedef unsigned short u16_t;
typedef unsigned char u8_t;
typedef struct 
{
	int w;
	int h;
	int bpp;
	void *fb_mem;
}info_t;


#endif

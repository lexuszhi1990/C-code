#ifndef __MAIN_H__
#define __MAIN_H__

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

extern int init_fb(info_t *fb);
extern int fb_pixel(info_t *fb, int x, int y, u32_t color);

extern int display(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display1(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display2(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display3(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display4(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display5(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display6(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display7(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display8(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display9(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display10(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display11(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display12(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display13(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display14(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display15(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display16(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display17(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
extern int display18(info_t *fb, int x, int y, info_t *jpeg_size, char *filename);
#endif


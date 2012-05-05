#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "main.h"

int init_fb(info_t *fb)
{
	printf("Init_fb\n");
	/* 1: open file */
	int fd = open("/dev/fb0", O_RDWR);
	if(fd < 0){
		perror("Error for open");
		exit(1);
	}
	printf("Open file Success\n")	;
	/* 2: r/w file */
	struct fb_var_screeninfo fb_var;
	if(ioctl(fd, FBIOGET_VSCREENINFO,
		    &fb_var) < 0){
		perror("Error for ioctl");
		exit(1);
	}
	int w = fb_var.xres;
	int h = fb_var.yres;
	int bpp = fb_var.bits_per_pixel;
	printf("w:%d\t h: %d\t bpp:%d\n",
		  w, h, bpp);

	int *fb_mem = mmap(NULL, w * h * bpp/8, PROT_READ|PROT_WRITE,
				    MAP_SHARED, fd, 0);
	if(fb_mem == MAP_FAILED){
		perror("Error for mmap");
		exit(1);
	}
	

	fb->w = w;
	fb->h = h;
	fb->bpp = bpp;
	fb->fb_mem = fb_mem;
	/* 3: close file */

	close(fd);
	return 0;
}

int fb_pixel(info_t *fb, int x, int y, u32_t color)
{
	u32_t *p = fb->fb_mem;
	*(p + x + y * fb->w) = color; /* ??? */
	return 0;
}

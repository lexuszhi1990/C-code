#include "common.h"

fb_info_t *fb_init(const char *dev_name, fb_info_t *fb)
{
	int fd, res; char *p;
	static fb_info_t bakup, *rfb = NULL;
	struct fb_var_screeninfo fb_var; 

	if(dev_name == NULL)
		dev_name = DFT_DEV; 
	if(fb == NULL)
		fb = &bakup;	

	fd = open(dev_name, O_RDWR);
	if(fd == -1)
		goto err_open;	
	res = ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
	if(res == -1)
		goto err_other;
	
	fb->x_res = fb_var.xres;
	fb->y_res = fb_var.yres;
	fb->bpp = fb_var.bits_per_pixel;

	p = (char *)mmap(NULL, fb->x_res * fb-> y_res * fb->bpp / 8, 
				PROT_READ | PROT_WRITE, MAP_SHARED, 
				fd, 0);
	if(p == MAP_FAILED)
		goto err_other;
	fb->fb_buf = p;
	rfb = fb;

err_other:
	close(fd);
err_open:
	return rfb;
}

int fb_destroy(fb_info_t *fb)
{
	if(fb == NULL)
		return -1;
	munmap(fb->fb_buf, fb->x_res * fb->y_res * fb->bpp / 8);
	fb->x_res = fb->y_res = fb->bpp = 0;

	return 0;
}

void disppix(const fb_info_t *fb, int x, int y, u32_t color)
{
	char *p;

	if(fb == NULL) return;
	p = fb->fb_buf;
	p = p + (y * fb->x_res + x) * fb->bpp / 8;
	*((u32_t *)p) = color;
}

void displn(const fb_info_t *fb, int x, int y, u32_t color, int len)
{
	int i;
	
	for(i = 0; i < len; i++)
		disppix(fb, x + i, y, color);
}

void dispvln(const fb_info_t *fb, int x, int y, u32_t color, int hight
)
{
	int i;

	for(i = 0; i < hight; i++)
		disppix(fb, x, y + i, color);

}

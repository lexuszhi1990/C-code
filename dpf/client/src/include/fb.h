#ifndef FB_H_
#define FB_H_

#define DFT_DEV "/dev/fb0"

extern fb_info_t *fb_init(const char *dev_name, fb_info_t *fb);
extern int fb_destroy(fb_info_t *fb);
extern void disppix(const fb_info_t *fb, int x, int y, u32_t color);
extern void displn(const fb_info_t *fb, int x, int y, u32_t color, int len);
extern void dispvln(const fb_info_t *fb, int x, int y, u32_t color, int hight);

#endif

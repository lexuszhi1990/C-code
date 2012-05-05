#ifndef EFFECT_H_
#define EFFECT_H_

#define HAND_NUM 4

extern handler_t handler[];

extern int disp_jpeg(const char *filename, fb_info_t fb_inf);
extern int disp_jpeg_rev(const char *filename, fb_info_t fb_inf);
extern int display_jpeg_ver(const char *filename, fb_info_t fb_inf);
extern int display_jpeg_ver_rev(const char *filename, fb_info_t fb_inf);

#endif 

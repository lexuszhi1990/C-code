#ifndef JPEG_H_
#define JPEG_H_

extern u8_t *decode_jpeg (const char *filename, fb_info_t *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, fb_info_t jpeg_inf);
extern u8_t * scale24(u8_t *buf24, fb_info_t new_inf, fb_info_t jpeg_inf);

#endif

#include "common.h"

handler_t handler[HAND_NUM] = { disp_jpeg, 
				disp_jpeg_rev, 
				display_jpeg_ver, 
				display_jpeg_ver_rev
				};

/* from top to buttom */
int disp_jpeg(const char *filename, fb_info_t fb_inf)
{

	fb_info_t original_jpeg, new_jpeg;
	int i, j;
	u8_t *buf24, *scale_buf;
	u32_t *buf32;
	
	new_jpeg = fb_inf;
	buf24 = decode_jpeg(filename, &original_jpeg);
	if(buf24 == NULL)
		return 0;
	scale_buf = scale24(buf24, new_jpeg, original_jpeg);
	if(scale_buf == NULL)
		return 0;
	buf32 = rgb24to32(scale_buf, new_jpeg);
	if(buf32 == NULL)
		return 0;
	
	for(i = 0; i < new_jpeg.y_res; ++i){
		for (j = 0; j < new_jpeg.x_res; ++j){
			disppix(&fb_inf, j, i, buf32[j + i * new_jpeg.x_res]);
		}
		usleep(1000);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

/* from buttom to top */
int disp_jpeg_rev(const char *filename, fb_info_t fb_inf)
{

	fb_info_t original_jpeg, new_jpeg;
	int i, j;
	u8_t *buf24, *scale_buf;
	u32_t *buf32;
	
	new_jpeg = fb_inf;
	buf24 = decode_jpeg(filename, &original_jpeg);
	if(buf24 == NULL)
		return 0;
	scale_buf = scale24(buf24, new_jpeg, original_jpeg);
	if(scale_buf == NULL)
		return 0;
	buf32 = rgb24to32(scale_buf, new_jpeg);
	if(buf32 == NULL)
		return 0;

	for(i = new_jpeg.y_res - 1; i >= 0; i--){
		for (j = 0; j < new_jpeg.x_res; ++j){
			disppix(&fb_inf, j, i, buf32[j + i * new_jpeg.x_res]);
		}
		usleep(1000);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

/* from left to right */
int display_jpeg_ver(const char *filename, fb_info_t fb_inf)
{

	fb_info_t original_jpeg, new_jpeg;
	int i, j;
	u8_t *buf24, *scale_buf;
	u32_t *buf32;
	
	new_jpeg = fb_inf;
	buf24 = decode_jpeg(filename, &original_jpeg);
	if(buf24 == NULL)
		return 0;
	scale_buf = scale24(buf24, new_jpeg, original_jpeg);
	if(scale_buf == NULL)
		return 0;
	buf32 = rgb24to32(scale_buf, new_jpeg);
	if(buf32 == NULL)
		return 0;
	
	for (j = 0; j < new_jpeg.x_res; ++j){
		for(i = 0; i < new_jpeg.y_res; ++i){
			disppix(&fb_inf, j, i, buf32[j + i * new_jpeg.x_res]);
		}
		usleep(1000);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

/* from right to left */
int display_jpeg_ver_rev(const char *filename, fb_info_t fb_inf)
{

	fb_info_t original_jpeg, new_jpeg;
	int i, j;
	u8_t *buf24, *scale_buf;
	u32_t *buf32;
	
	new_jpeg = fb_inf;
	buf24 = decode_jpeg(filename, &original_jpeg);
	if(buf24 == NULL)
		return 0;
	scale_buf = scale24(buf24, new_jpeg, original_jpeg);
	if(scale_buf == NULL)
		return 0;
	buf32 = rgb24to32(scale_buf, new_jpeg);
	if(buf32 == NULL)
		return 0;
	
	for (j = new_jpeg.x_res - 1; j >= 0; j--){
		for(i = 0; i < new_jpeg.y_res; ++i){
			disppix(&fb_inf, j, i, buf32[j + i * new_jpeg.x_res]);
		}
		usleep(1000);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

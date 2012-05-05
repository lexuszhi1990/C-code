#include<stdlib.h>
#include"main.h"
#include<unistd.h>
extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);

int display2(info_t*fb, int x, int y,info_t *jpeg_size,char *filename)
{
	
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename,&jpeg);
	u8_t *buf24=scale24(buf,jpeg_size,&jpeg);
	u32_t *buf32=rgb24to32(buf24,jpeg_size);
	int i,j;
	for(i=0;i<jpeg_size->w/8;++i)
	{
	//int n = jpeg_size->h/2;
		for(j = 0;j< jpeg_size->h; ++j)
			{	int n = jpeg_size->w/8;	
				fb_pixel(fb, i+x, y+j,buf32[i+j*jpeg_size->w]);
			    fb_pixel(fb, i+x+n, y+j,buf32[i+n+j*jpeg_size->w]);
				fb_pixel(fb, i+x+2*n, y+j,buf32[i+2*n+j*jpeg_size->w]);			
				fb_pixel(fb, i+x+3*n, y+j,buf32[i+3*n+j*jpeg_size->w]);
				fb_pixel(fb, i+x+4*n, y+j,buf32[i+4*n+j*jpeg_size->w]);
				fb_pixel(fb, i+x+5*n, y+j,buf32[i+5*n+j*jpeg_size->w]);
				fb_pixel(fb, i+x+6*n, y+j,buf32[i+6*n+j*jpeg_size->w]);
				fb_pixel(fb, i+x+7*n, y+j,buf32[i+7*n+j*jpeg_size->w]);
			//for(i = 0;i < jpeg_size->w; ++i)
					//fb_pixel(fb, i+x, y+n+j,buf32[i+(n+j)*jpeg_size->w]);
				//usleep(1);
			}	
		usleep(1000);
	}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}  

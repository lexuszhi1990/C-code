#include<stdlib.h>
#include"main.h"
#include<unistd.h>
extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);

int display(info_t*fb, int x, int y,info_t *jpeg_size,char *filename)
{
	
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename,&jpeg);
	u8_t *buf24=scale24(buf,jpeg_size,&jpeg);
	u32_t *buf32=rgb24to32(buf24,jpeg_size);
	int i,j;
	for(j=0;j<jpeg_size->h/8;++j)
	{
		for(i = 0;i< jpeg_size->w; ++i)
			{	int n = jpeg_size->h/8;	
				fb_pixel(fb, i+x, y+j,buf32[i+j*jpeg_size->w]);
			    fb_pixel(fb, i+x, y+n+j,buf32[i+(j+n)*jpeg_size->w]);
				fb_pixel(fb, i+x, y+2*n+j,buf32[i+(j+2*n)*jpeg_size->w]);			
				fb_pixel(fb, i+x, y+3*n+j,buf32[i+(j+3*n)*jpeg_size->w]);
				fb_pixel(fb, i+x, y+4*n+j,buf32[i+(j+4*n)*jpeg_size->w]);
				fb_pixel(fb, i+x, y+5*n+j,buf32[i+(j+5*n)*jpeg_size->w]);
				fb_pixel(fb, i+x, y+6*n+j,buf32[i+(j+6*n)*jpeg_size->w]);
				fb_pixel(fb, i+x, y+7*n+j,buf32[i+(j+7*n)*jpeg_size->w]);

			}	
		usleep(1000);
	}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

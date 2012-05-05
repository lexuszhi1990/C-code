#include<stdlib.h>
#include <unistd.h>

#include"main.h"

extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);

int display1(info_t*fb,int x,int y,info_t *jpeg_size, char*filename)
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename,&jpeg);
	u8_t *buf24 = scale24(buf,jpeg_size,&jpeg);
	u32_t *buf32 = rgb24to32(buf24,jpeg_size);
	int i,j,t;
	for(t=680;t>0;t--)
		{
			for(j=0;j<jpeg_size->h;j++)
			{
				for(i=0;i<jpeg_size->w;i++)
				{
					if((i-jpeg_size->w/2)*(i-jpeg_size->w/2)+(j-jpeg_size->h/2)*(j-jpeg_size->h/2)>=t*t)
					{fb_pixel(fb,i+x,j+y,buf32[i+j*jpeg_size->w]);}
				}
			}
			usleep(100);
		}
	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

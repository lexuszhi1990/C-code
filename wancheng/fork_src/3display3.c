#include<stdlib.h>
#include <unistd.h>

#include"main.h"

extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);

int display3(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename,&jpeg);
	u8_t *buf24 = scale24(buf,jpeg_size,&jpeg);
	u32_t *buf32 = rgb24to32(buf24,jpeg_size);
	int i,j;
	int m=jpeg_size->h/6;
	int n=jpeg_size->w/6;
		for(i=0;i<=jpeg_size->w/6;++i)
			{ 
				for(j=0;j<=jpeg_size->h/6;++j)
				{	
					fb_pixel(fb,n*3-i+x,y+m*3-j,buf32[(n*3-i)+(m*3-j)*jpeg_size->w]);
					fb_pixel(fb,n*3+i+x,y+m*3+j,buf32[(n*3+i)+(m*3+j)*jpeg_size->w]);	
					fb_pixel(fb,n*3+i+x,y+m*3-j,buf32[(n*3+i)+(m*3-j)*jpeg_size->w]);			
					fb_pixel(fb,n*3-i+x,y+m*3+j,buf32[(n*3-i)+(m*3+j)*jpeg_size->w]);
				}
				usleep(1);
			}
		for(i=0;i<=jpeg_size->w/6;++i)
			{ 
				for(j=0;j<=jpeg_size->h/6;++j)
				{	
					fb_pixel(fb,n-i+x,y+m-j,buf32[(n-i)+(m-j)*jpeg_size->w]);
					fb_pixel(fb,n+i+x,y+m+j,buf32[(n+i)+(m+j)*jpeg_size->w]);
					fb_pixel(fb,n*5-i+x,y+m*5-j,buf32[(n*5-i)+(m*5-j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*5+j,buf32[(n*5+i)+(m*5+j)*jpeg_size->w]);
					fb_pixel(fb,n*1-i+x,y+m*5-j,buf32[(n*1-i)+(m*5-j)*jpeg_size->w]);
					fb_pixel(fb,n*1+i+x,y+m*5+j,buf32[(n*1+i)+(m*5+j)*jpeg_size->w]);
					fb_pixel(fb,n*5-i+x,y+m*1-j,buf32[(n*5-i)+(m*1-j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*1+j,buf32[(n*5+i)+(m*1+j)*jpeg_size->w]);
						
						
						
					fb_pixel(fb,n+i+x,y+m-j,buf32[(n+i)+(m-j)*jpeg_size->w]);			
					fb_pixel(fb,n-i+x,y+m+j,buf32[(n-i)+(m+j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*5-j,buf32[(n*5+i)+(m*5-j)*jpeg_size->w]);			
					fb_pixel(fb,n*5-i+x,y+m*5+j,buf32[(n*5-i)+(m*5+j)*jpeg_size->w]);
					fb_pixel(fb,n*1+i+x,y+m*5-j,buf32[(n*1+i)+(m*5-j)*jpeg_size->w]);			
					fb_pixel(fb,n*1-i+x,y+m*5+j,buf32[(n*1-i)+(m*5+j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*1-j,buf32[(n*5+i)+(m*1-j)*jpeg_size->w]);			
					fb_pixel(fb,n*5-i+x,y+m*1+j,buf32[(n*5-i)+(m*1+j)*jpeg_size->w]);
				}
					usleep(1);
			}
				
		for(i=0;i<=jpeg_size->w/6;++i)
			{ 
				for(j=0;j<=jpeg_size->h/6;++j)
				{	
					fb_pixel(fb,n*1-i+x,y+m*3-j,buf32[(n*1-i)+(m*3-j)*jpeg_size->w]);
					fb_pixel(fb,n*1+i+x,y+m*3+j,buf32[(n*1+i)+(m*3+j)*jpeg_size->w]);
					fb_pixel(fb,n*5-i+x,y+m*3-j,buf32[(n*5-i)+(m*3-j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*3+j,buf32[(n*5+i)+(m*3+j)*jpeg_size->w]);
					fb_pixel(fb,n*3-i+x,y+m*1-j,buf32[(n*3-i)+(m*1-j)*jpeg_size->w]);
					fb_pixel(fb,n*3+i+x,y+m*1+j,buf32[(n*3+i)+(m*1+j)*jpeg_size->w]);
					fb_pixel(fb,n*3-i+x,y+m*5-j,buf32[(n*3-i)+(m*5-j)*jpeg_size->w]);
					fb_pixel(fb,n*3+i+x,y+m*5+j,buf32[(n*3+i)+(m*5+j)*jpeg_size->w]);	


					fb_pixel(fb,n*1+i+x,y+m*3-j,buf32[(n*1+i)+(m*3-j)*jpeg_size->w]);			
					fb_pixel(fb,n*1-i+x,y+m*3+j,buf32[(n*1-i)+(m*3+j)*jpeg_size->w]);
					fb_pixel(fb,n*5+i+x,y+m*3-j,buf32[(n*1+i)+(m*3-j)*jpeg_size->w]);			
					fb_pixel(fb,n*5-i+x,y+m*3+j,buf32[(n*1-i)+(m*3+j)*jpeg_size->w]);
					fb_pixel(fb,n*3+i+x,y+m*1-j,buf32[(n*3+i)+(m*1-j)*jpeg_size->w]);			
					fb_pixel(fb,n*3-i+x,y+m*1+j,buf32[(n*3-i)+(m*1+j)*jpeg_size->w]);
					fb_pixel(fb,n*3+i+x,y+m*5-j,buf32[(n*3+i)+(m*5-j)*jpeg_size->w]);			
					fb_pixel(fb,n*3-i+x,y+m*5+j,buf32[(n*3-i)+(m*5+j)*jpeg_size->w]);
				}
				usleep(1);
			}

	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

#include <stdlib.h>
#include <unistd.h>
#include "main.h"

extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);

int display(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int p, q = 30;
	
	for(i = 0; i < jpeg_size->w/2; ++i)
	{
		int n = jpeg_size->w/2 ;
		for(j = 0; j < jpeg_size->h; ++j)
		{
			fb_pixel(fb, x+n-i, y+j, buf32[(n-i) + j * jpeg_size->w]);
		}
		for(j = 0; j < jpeg_size->h; ++j)
		{
			fb_pixel(fb, x+n+i, y+j, buf32[(n+i) + j * jpeg_size->w]);
		}	
								

		
			
		if((i+q) > (jpeg_size->w/2)) q--;
		
		for(p = 1; p < q; ++p)
		{
			for(j = 0; j < jpeg_size->h; ++j)
			{
				fb_pixel(fb, x+n+i+p, y+j, buf32[(i+n+q-p) + j * jpeg_size->w]);
			}	
			for(j = 0; j < jpeg_size->h; ++j)
			{
				fb_pixel(fb, x+n-i-p, y+j, buf32[(n-i-(q-p)) + j * jpeg_size->w]);
			}	
		}


			
		usleep(5000);
	}

	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

	/*int i, j;
	int m, n = 50;
	int k, r = 50;
	for(i = 0; i < jpeg_size->w/2; ++i){
		for(j = 0; j < jpeg_size->h; ++j){
		int l=jpeg_size->w/2;
			fb_pixel(fb, x+l-i, y+j, buf32[l-i + j * jpeg_size->w]);
			if(i <= r) r--;
			for(k = 1; k < r; ++k)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, x+i-k, y+j, buf32[(i+r+k) + j * jpeg_size->w]);
		}
	
	
		for(j = 0; j < jpeg_size->h; ++j){
			fb_pixel(fb, i+x+l, y+j, buf32[i+l + j * jpeg_size->w]);
			if(i+n > jpeg_size->w) n--;
			for(m = 1; m < n; ++m)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, i+x+m, y+j, buf32[(i+n-m) + j * jpeg_size->w]);
		}
}	
	*/
int display1(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)  /*congshangdaoxiadakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	for(j = 0; j < jpeg_size->h; ++j){
		for(i = 0; i < jpeg_size->w; ++i)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);
		usleep(3000);
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display2(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zhongjianshangxiadakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	for(j = 0; j < jpeg_size->h/2; ++j){
		int n = jpeg_size->h/2 ;
		for(i = 0; i < jpeg_size->w; ++i)
			fb_pixel(fb, i+x, y+n-j, buf32[i + (n-j) * jpeg_size->w]);
		for(i = 0; i < jpeg_size->w; ++i)
			fb_pixel(fb, i+x, y+n+j, buf32[i + (n+j) * jpeg_size->w]);
		usleep(5000);
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display3(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*juanzhou congshangwangxia*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int m, n = 50;
	for(j = 0; j < jpeg_size->h; ++j){
		for(i = 0; i < jpeg_size->w; ++i)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);

		if(n+j > jpeg_size->h) n--;

		for(m = 1; m < n; ++m)
			for(i = 0; i < jpeg_size->w; ++i)
				fb_pixel(fb, i+x, y+j+m, buf32[i + (j+n-m) * jpeg_size->w]);

		usleep(4000);
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display4(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*congzuodaoyoudakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	for(i = 0; i< jpeg_size->w; ++i){
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);
		usleep(3000);
	}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display5(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zhongjianzuoyoudakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	for(i = 0; i < jpeg_size->w/2; ++i){
		int n = jpeg_size->w/2 ;
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, x+n-i, y+j, buf32[(n-i) + j * jpeg_size->w]);
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, x+n+i, y+j, buf32[(n+i) + j * jpeg_size->w]);
		usleep(5000);
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display6(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*juanzhou congxiadaoshang*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int m, n = 50;
	for(j = jpeg_size->h; j >=0; --j){
		for(i = 0; i < jpeg_size->w; ++i)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);

		if(j <= n) n--;

		for(m = 1; m < n; ++m)
			for(i = 0; i < jpeg_size->w; ++i)
				fb_pixel(fb, i+x, y+j-m, buf32[i + (j+n+m) * jpeg_size->w]);

		usleep(4000);
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display7(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*juanzhou congyoudaozuo*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int m, n = 50;
	for(i = jpeg_size->w; i >=0; --i){
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);

		if(i <= n) n--;

		for(m = 1; m < n; ++m)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, i+x-m, y+j, buf32[(i+n+m) + j * jpeg_size->w]);
                                   

		usleep(3000);
	}
	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

int display8(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*juanzhou congzuodaoyou */
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int m, n = 50;
	for(i = 0; i < jpeg_size->w; ++i){
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, i+x, y+j, buf32[i + j * jpeg_size->w]);

		if(i+n > jpeg_size->w) n--;

		for(m = 1; m < n; ++m)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, i+x+m, y+j, buf32[(i+n-m) + j * jpeg_size->w]);


		usleep(3000);
	}
	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

/*int display8(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j,l=jpeg_size->w/2 ;
	int m, n = 50;
	int k, r = 50;
	for(i = jpeg_size->w/2; i >=0; --i){
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, i+x+l, y+j, buf32[i + j * jpeg_size->w]);
		if(i <= r) r--;
		for(k = 1; k < r; ++k)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, i+x-k, y+j, buf32[(i+r+k) + j * jpeg_size->w]);
	};
	for(i = jpeg_size->w/2; i < jpeg_size->w; ++i){
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, i+x+l, y+j, buf32[i + j * jpeg_size->w]);
		if(i+n > jpeg_size->w) n--;
		for(m = 1; m < n; ++m)
			for(j = 0; j < jpeg_size->h; ++j)
				fb_pixel(fb, i+x+m, y+j, buf32[(i+n-m) + j * jpeg_size->w]);
	}	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}*/
int display9(info_t*fb,int x,int y,info_t *jpeg_size, char*filename)/*yuan zhongjiandaozhouwei*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename,&jpeg);
	u8_t *buf24 = scale24(buf,jpeg_size,&jpeg);
	u32_t *buf32 = rgb24to32(buf24,jpeg_size);
	int i,j,t;
	for(t=0;t<680;t++)
		{
			for(j=0;j<jpeg_size->h;j++)
			{
				for(i=0;i<jpeg_size->w;i++)
				{
				if((i-jpeg_size->w/2)*(i-jpeg_size->w/2)+(j-jpeg_size->h/2)*(j-jpeg_size->h/2)<t*t)
					{fb_pixel(fb,i+x,j+y,buf32[i+j*jpeg_size->w]);}
				}
			}
			usleep(80);
		}
	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

int display10(info_t*fb,int x,int y,info_t *jpeg_size, char*filename)/*yuan zhouweidaozhongjian*/
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
			usleep(80);
		}
	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

int display11(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*jiukuai jiangedakai*/
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
				usleep(10000);
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
					usleep(10000);
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
				usleep(10000);
			}

	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}


int display12(info_t*fb, int x, int y,info_t *jpeg_size,char *filename) /*hengxiangbaiyechuang*/
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
		usleep(50000);
	}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
		
}


int display13(info_t*fb, int x, int y,info_t *jpeg_size,char *filename)/*zongxiangbaiyechuang*/
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
		usleep(50000);
	}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
		
} 
int display14(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zhongjianzuoyoudakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	
	int i, j;
	int p, q = 30;
	for(i = 0; i <jpeg_size->w; ++i){
	
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, x+i, y+j, buf32[i + j * jpeg_size->w]);
		for(j = 0; j < jpeg_size->h; ++j)
			fb_pixel(fb, x+jpeg_size->w-i, y+j, buf32[(jpeg_size->w-i) + j * jpeg_size->w]);

			
		if(( jpeg_size->w/2-i)<30) q--;
		
		for(p = 1; p < q; ++p)
		{
			for(j = 0; j < jpeg_size->h; ++j)
			{
				fb_pixel(fb, x+i+p, y+j, buf32[(i+p+q) + j * jpeg_size->w]);
			}	
			for(j = 0; j < jpeg_size->h; ++j)
			{
				fb_pixel(fb, x+jpeg_size->w-i-p, y+j, buf32[(jpeg_size->w-i-(q-p)) + j * jpeg_size->w]);
			}	
		}



		usleep(2000);
		
	}
	/*	...*/
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
int display15(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*feixia*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	int i,j,t;
	for(j=0;j<jpeg_size->h;++j)
		{
			for(t=0;t<j;++t)
			for(i=0;i<jpeg_size->w;++i)
			{				
				fb_pixel(fb,x+i,y+t,buf32[i+(jpeg_size->h-j+t)*jpeg_size->w]);
			
			}		
		}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}



int display16(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zhongjianzuoyoudakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	int i,j,t;
	for(j=0;j<jpeg_size->h;++j)
		{
			for(t=0;t<j;++t)
			for(i=0;i<jpeg_size->w;++i)
			{				
				fb_pixel(fb,x+i,y+t,buf32[i+(jpeg_size->h-j+t)*jpeg_size->w]);
			
			}		
		}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}







int display17(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zhongjianzuoyoudakai*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	int i,j;
 	int a;
	for(j=0;j<jpeg_size->h;++j)
	
			{
			for(i=0;i<jpeg_size->w;++i)
				fb_pixel(fb,x+i,y+jpeg_size->h-j,buf32[i+(y+jpeg_size->h-j)*jpeg_size->w]);
			        for(a=0;a<jpeg_size->h-j;++a)
			        	for(i=0;i<jpeg_size->w;++i)
			        	fb_pixel(fb,x+i,y+a,buf32[i+(y+jpeg_size->h-j+1)*jpeg_size->w]);
			   	
			}	
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}	
	


int display18(info_t *fb, int x, int y, info_t *jpeg_size, char *filename)/*zuoyoufeiru*/
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24, jpeg_size);
	int i,j,t;
		for(i=0;i<jpeg_size->w;++i)
		{
			for(t=0;t<i;++t)
			for(j=0;j<jpeg_size->h;++j)
			{				
				fb_pixel(fb,x+t,y+j,buf32[(jpeg_size->w-i+t)+j*jpeg_size->w]);
			
			}		
		}
	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}
#include <string.h>
int fb_clear(info_t* fb)
{
	memset(fb->fb_mem, 0, fb->w * fb->h * fb->bpp/8);
	return 0;
}









#include<stdlib.h>
#include <unistd.h>
#include<math.h>
#include"main.h"

extern u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, info_t *jpeg);
extern u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg);

int display(info_t *fb,int x,int y,info_t *jpeg_size,char *filename)
{
	info_t jpeg;
	u8_t *buf = decode_jpeg(filename, &jpeg);
	u8_t *buf24 = scale24(buf, jpeg_size, &jpeg);
	u32_t *buf32 = rgb24to32(buf24,jpeg_size);
	
	int i,j,t;

/*  shangzhixia
	for(j=0;j<jpeg_size->h;++j)
		for(t=0;t<=j;t++)
			for(i=0;i<jpeg_size->w;++i)
				fb_pixel(fb,x+i,y+j,buf32[i+j*jpeg_size->w]);

*/

/*  daofang
	for(j=0;j<jpeg_size->h;++j)
		{
			
			for(i=0;i<jpeg_size->w;++i)
			fb_pixel(fb,x+i,y+j,buf32[i+(jpeg_size->h-j)*jpeg_size->w]);
		}
*/

/* feixia
	for(j=0;j<jpeg_size->h;++j)
		{
			for(t=0;t<j;++t)
			for(i=0;i<jpeg_size->w;++i)
			{				
				fb_pixel(fb,x+i,y+t,buf32[i+(jpeg_size->h-j+t)*jpeg_size->w]);
			
			}		
		}

*/

/*  zuo you feiru 
	for(i=0;i<jpeg_size->w;++i)
		{
			for(t=0;t<i;++t)
			for(j=0;j<jpeg_size->h;++j)
			{				
				fb_pixel(fb,x+t,y+j,buf32[(jpeg_size->w-i+t)+j*jpeg_size->w]);
			
			}		
		}
*/

/*
	for(j=jpeg_size->h;j>0;--j)
		{
			for(t=jpeg_size->h;t>=j;--t)
			for(i=0;i<jpeg_size->w;++i)
			{				
				fb_pixel(fb,x+i,y+t,buf32[i+(t-j)*jpeg_size->w]);
			
			}		
		}
*/
	
/*  juanzhou
	int m,n=40;
	for(j=0;j<jpeg_size->h;++j)
		{

			for(i=0;i<jpeg_size->w;++i)
							
				fb_pixel(fb,x+i,y+j,buf32[i+j*jpeg_size->w]);
				
				if(n+j>jpeg_size->h) n--;
				for(m=1;m<n;++m)
					for(i=0;i<jpeg_size->w;++i)
					fb_pixel(fb,x+i,y+j+m,buf32[i+(j+n-m)*jpeg_size->w]);
							usleep(10000);	
		}		
*/		



/*  xiexia

	for(i=0;i<1025;++i)
		{
			for(t=i;t>0;--t)
				{			
					fb_pixel(fb,x+t,y+i-t,buf32[y+(i-t)*jpeg_size->w]);
								
		
				}
			usleep(1);		
		}
*/	
   /* waiyuan
	   for (j=0;j<769;j++)
	      for(i=0;i<1025;i++)
	     
	   {
	          //usleep(1);   
	         for(t=450;t>=0;t--)
			  { for (j=0;j<767;j++)
			     for(i=0;i<1023;i++)
			      {   
				    if(t*t<=(i-511)*(i-511)/10+(j-383)*(j-383)/10)
				    { 
				  	  fb_pixel(fb,x+i,y+j,buf32[i+j*jpeg_size->w]);
				    //display(&fb , 0, 0,&jpeg_size, "test1.jpg");
				    }
	                       }
	                    }
	    }
*/
   /*neiyuan
	   for (j=0;j<769;j++)
	      for(i=0;i<1025;i++)	     
	   {
 
	         for(t=0;t<100;t++)
			  { for (j=0;j<767;j++)
				     for(i=0;i<1023;i++)
					{   
						    if(t*t>(i-511)*(i-511)/10+(j-383)*(j-383)/10)
						    { 
						  	  fb_pixel(fb,x+i,y+j,buf32[i+j*jpeg_size->w]);
						    }
			            }
	               }
	    }
*/
				
	
  for(i=0;i<jpeg_size->w/2;++i)
           for(j=0;j<jpeg_size->h/2;++j)
              {     usleep(10000);
		    int n= jpeg_size->h/2;
		     int m= i<jpeg_size->w/2;
		    for(i=0;i<jpeg_size->w/2;++i)
		    fb_pixel(fb,x+m-i,y+n-j,buf32[(m-i)+(n-j)*jpeg_size->w]);
	            for(i=0;i<jpeg_size->w/2;++i)
			fb_pixel(fb,i+m+x,y+n+j,buf32[(m+i)+(n+j)*jpeg_size->w]);
			//usleep(100);
			
		}
 






	free(buf);
	free(buf24);
	free(buf32);
	return 0;
}

















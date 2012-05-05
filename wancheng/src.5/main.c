#include <stdio.h>
#include <unistd.h>
#include "main.h"
char *jpeg[512]={
	"1.jpg",
	"2.jpg",
	"3.jpg",
	"4.jpg",
	"5.jpg",
	"6.jpg",
	"7.jpg",
	"8.jpg",
	"9.jpg",
	"10.jpg",
	"11.jpg",
	"12.jpg",
	"13.jpg",
	"14.jpg",
	"15.jpg",
	"16.jpg",
	"17.jpg",
	"18.jpg",
	"19.jpg",
	//"20.jpg",	
	NULL
	// ...
};
int main(void)
{
	info_t fb;
	init_fb(&fb);
	info_t jpeg_size = fb;
	int i = 0; 	int j = 0;
	while(1){
		if(jpeg[i] == NULL) i = 0;
		switch(j){
			case 0: 
				display(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 1:
				display1(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 2:
				display2(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 3:
				display3(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 4:
				display4(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 5:
				display5(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 6:
				display6(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 7:
				display7(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 8:
				display8(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 9:
				display9(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 10:
				display10(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 11:
				display11(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 12:
				display12(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 13:
				display13(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 14:
				display14(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 15:
				display15(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 16:
				display16(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 17:
				display17(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
			case 18:
				display17(&fb, 0, 0, &jpeg_size, jpeg[i]); break;
				
			default: j = -1;i--;
			
		}
		i++; j++;
		
		usleep(2000);	
		
		
	}
	return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <jpeglib.h>
#include <jerror.h>

#include <time.h>

#ifndef u_char
#define u_char unsigned char
#endif		


#include "main.h"

static void jpeg_error_exit (j_common_ptr cinfo) {
  cinfo->err->output_message (cinfo);
  exit (EXIT_FAILURE);
}


/*This returns an array for a 24 bit image.*/
u8_t *decode_jpeg (const char *filename, info_t *jpeg_inf)
{
	register JSAMPARRAY lineBuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err_mgr;
	int bytesPerPix;
	FILE *inFile;
	u_char *retBuf;
	
	inFile = fopen (filename, "rb");
	if (NULL == inFile)	{ 
		fprintf (stderr, "Error Open %s: %s\n",
			    filename, strerror(errno));
		return NULL;
	}

	cinfo.err = jpeg_std_error (&err_mgr);
	err_mgr.error_exit = jpeg_error_exit;	

	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, inFile);
	jpeg_read_header (&cinfo, 1);
	cinfo.do_fancy_upsampling = 0;
	cinfo.do_block_smoothing = 0;
	jpeg_start_decompress (&cinfo);

	/* 2010.2.6 By Panda.Guo and some... */
	jpeg_inf->w = cinfo.output_width;
	jpeg_inf->h = cinfo.output_height;

	short w,h;
	short *widthPtr = &w;
	short *heightPtr = &h;
	w = jpeg_inf->w;
	h = jpeg_inf->h;
	

	bytesPerPix = cinfo.output_components;

	lineBuf = cinfo.mem->alloc_sarray ((j_common_ptr) &cinfo, JPOOL_IMAGE, (*widthPtr * bytesPerPix), 1);
	retBuf = (u_char *) malloc (3 * (*widthPtr * *heightPtr));
		
	if (NULL == retBuf) {
		perror (NULL);
		return NULL;
	}
		

	if (3 == bytesPerPix) {
		int y;
			
		for (y = 0; y < cinfo.output_height; ++y)	{	
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
			memcpy ((retBuf + y * *widthPtr * 3),lineBuf[0],3 * *widthPtr);
		}
	}
	else if (1 == bytesPerPix) { 
		unsigned int col;
		int lineOffset = (*widthPtr * 3);
		int lineBufIndex;
		int x ;
		int y;
						
		for (y = 0; y < cinfo.output_height; ++y) {
			jpeg_read_scanlines (&cinfo, lineBuf, 1);
				
			lineBufIndex = 0;
			for (x = 0; x < lineOffset; ++x) {
				col = lineBuf[0][lineBufIndex];
			
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				++x;
				retBuf[(lineOffset * y) + x] = col;
				
				++lineBufIndex;
			}			
		}
	}
	else {
		fprintf (stderr, "Error: the number of color channels is %d.  This program only handles 1 or 3\n", bytesPerPix);
		return NULL;
	}
	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);
	fclose (inFile);
			
	return retBuf;
}


/* By Panda.Guo at 2010.2.6 */
u32_t * rgb24to32(u8_t *buf24, info_t *jpeg)
#if 1
{
	int w = jpeg->w;
	int h = jpeg->h;
	
	u32_t *buf = malloc(w * h * 4);
	if (buf == NULL) return NULL;

	int i;
	for(i = 0; i < w * h; ++i){
		*((u8_t *)&buf[i] + 2) = buf24[i * 3 + 0];
		*((u8_t *)&buf[i] + 1) = buf24[i * 3 + 1];
		*((u8_t *)&buf[i] + 0) = buf24[i * 3 + 2];
		*((u8_t *)&buf[i] + 3) = 0x00;
	}
	return (u32_t *)buf;
}


/* By Panda.Guo at 2010-2-10 add ... */
u16_t * rgb24to16(u8_t *buf24, info_t* jpeg)
#endif
{
	u16_t *buf16 = NULL;
	
	u32_t r24,g24,b24;
	u32_t r16,g16,b16;
	u16_t rgb16;
	int i;

	if ((buf16 = malloc (jpeg->w * jpeg->h * 2)) == NULL)
		return NULL;

	for (i = 0 ;i < jpeg->w * jpeg->h ; i++)	{

		r24 = buf24[i * 3 + 0];
		g24 = buf24[i * 3 + 1];
		b24 = buf24[i * 3 + 2];	

		b16 = (b24 * 0x1f) / 0xff;
		g16 = (g24 * 0x3f) / 0xff;
		r16 = (r24 * 0x1f) / 0xff;
	
		rgb16 = b16 | (g16 <<5) | (r16 <<11);
	
		buf16[i] = rgb16;
	}
	return buf16;
}

/* By Panda.Guo at 2010.2.15 add ... */
u8_t * scale24(u8_t *buf24, info_t* new, info_t* jpeg)
{
	int i,j;
	int dtw,dth;
	
	u8_t *buf = malloc(new->w * new->h * 3);

	if (buf == NULL) return NULL;
	
	for(j = 0; j < new->h; j++){
		for(i = 0; i < new->w; i++){

			dtw = i * jpeg->w / new->w;
			dth = j * jpeg->h / new->h;

			buf[0+i*3 + j*new->w*3] = 
				buf24[0+(dtw+dth*jpeg->w)*3];

			buf[1+i*3 + j*new->w*3] = 
				buf24[1+(dtw+dth*jpeg->w)*3];
			
			buf[2+i*3 + j*new->w*3] =
				buf24[2+(dtw+dth*jpeg->w)*3];
		}
	}

	return buf;
}

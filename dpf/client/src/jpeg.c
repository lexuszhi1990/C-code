/*Copyright George Peter Staplin 2003*/

/*You may use/copy/modify/distribute this software for any purpose
 *provided that I am given credit and you don't sue me for any bugs.
 */

/*Please contact me using GeorgePS@XMission.com if you like this, or
 *have questions.
 */
#include "common.h"

static void jpeg_error_exit (j_common_ptr cinfo) {
  cinfo->err->output_message (cinfo);
  exit (EXIT_FAILURE);
}

/*This returns an array for a 24 bit image.*/
u8_t *decode_jpeg (const char *filename, fb_info_t *jpeg_inf)
{
	register JSAMPARRAY lineBuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err_mgr;
	int bytesPerPix;
	FILE *inFile;
	u8_t *retBuf;
	
	inFile = fopen (filename, "rb");
	if(NULL == inFile)
		return NULL;

	cinfo.err = jpeg_std_error (&err_mgr);
	err_mgr.error_exit = jpeg_error_exit;	

	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, inFile);
	jpeg_read_header (&cinfo, 1);
	cinfo.do_fancy_upsampling = 0;
	cinfo.do_block_smoothing = 0;
	jpeg_start_decompress (&cinfo);

	/* 2010.2.6 and some... */
	jpeg_inf->x_res = cinfo.output_width;
	jpeg_inf->y_res = cinfo.output_height;

	short w,h;
	short *widthPtr = &w;
	short *heightPtr = &h;
	w = jpeg_inf->x_res;
	h = jpeg_inf->y_res;
	

	bytesPerPix = cinfo.output_components;

	lineBuf = cinfo.mem->alloc_sarray ((j_common_ptr) &cinfo, JPOOL_IMAGE, (*widthPtr * bytesPerPix), 1);
	retBuf = (u8_t *) malloc (3 * (*widthPtr * *heightPtr));
		
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

/* XXX: 2010.2.5, by Tony add function  */
u32_t *rgb24to32(u8_t *buf24, fb_info_t jpeg_inf)
{
	int w = jpeg_inf.x_res;
	int h = jpeg_inf.y_res;
	
	u32_t *buf = malloc(w * h * 4);
	if (buf == NULL) return NULL;

	/* FIXME: why? */
	int i;
	for(i = 0; i < w * h; ++i){
		*((u8_t *)&buf[i] + 2) = buf24[i * 3 + 0];
		*((u8_t *)&buf[i] + 1) = buf24[i * 3 + 1];
		*((u8_t *)&buf[i] + 0) = buf24[i * 3 + 2];
		*((u8_t *)&buf[i] + 3) = 0x00;
	}
	return (u32_t *)buf;
}

/* XXX: 2010.4.5 add function by Tony  */
u16_t * rgb24to16(u8_t *buf24, fb_info_t jpeg_inf)
{
	u16_t *buf16 = NULL;
	
	u32_t r24,g24,b24;
	u32_t r16,g16,b16;
	u16_t rgb16;
	int i;

	if ((buf16 = malloc (jpeg_inf.x_res * jpeg_inf.y_res * 2)) == NULL)
		return NULL;
	for (i = 0 ;i < jpeg_inf.x_res * jpeg_inf.y_res ; i++){

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

u8_t * scale24(u8_t *buf24, fb_info_t new_inf, fb_info_t jpeg_inf)
{
	int i,j;
	int dtw,dth;
	
	u8_t *buf = malloc(new_inf.x_res * new_inf.y_res * 3);

	if (buf == NULL) 
		return NULL;
	
	for(j = 0; j < new_inf.y_res; j++){
		for(i = 0; i < new_inf.x_res; i++){

			dtw = i * jpeg_inf.x_res / new_inf.x_res;
			dth = j * jpeg_inf.y_res / new_inf.y_res;

			buf[0+i*3 + j*new_inf.x_res*3] = 
				buf24[0+(dtw+dth*jpeg_inf.x_res)*3];

			buf[1+i*3 + j*new_inf.x_res*3] = 
				buf24[1+(dtw+dth*jpeg_inf.x_res)*3];
			
			buf[2+i*3 + j*new_inf.x_res*3] =
				buf24[2+(dtw+dth*jpeg_inf.x_res)*3];
		}
	}

	return buf;
}

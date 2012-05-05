#include "common.h"

static const u32_t cursor[C_WIDTH * C_HEIGHT] = {
  BORD, T___, T___, T___, T___, T___, T___, T___, T___, T___,
  BORD, BORD, T___, T___, T___, T___, T___, T___, T___, T___,
  BORD, X___, BORD, T___, T___, T___, T___, T___, T___, T___,
  BORD, X___, X___, BORD, T___, T___, T___, T___, T___, T___,
  BORD, X___, X___, X___, BORD, T___, T___, T___, T___, T___,
  BORD, X___, X___, X___, X___, BORD, T___, T___, T___, T___,
  BORD, X___, X___, X___, X___, X___, BORD, T___, T___, T___,
  BORD, X___, X___, X___, X___, X___, X___, BORD, T___, T___,
  BORD, X___, X___, X___, X___, X___, X___, X___, BORD, T___,
  BORD, X___, X___, X___, X___, X___, X___, X___, X___, BORD,
  BORD, X___, X___, X___, X___, X___, BORD, BORD, BORD, BORD,
  BORD, X___, X___, BORD, X___, X___, BORD, T___, T___, T___,
  BORD, X___, BORD, T___, BORD, X___, X___, BORD, T___, T___,
  BORD, BORD, T___, T___, BORD, X___, X___, BORD, T___, T___,
  T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
  T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
  T___, T___, T___, T___, T___, T___, BORD, BORD, T___, T___
};
static u32_t cursor_saver[C_WIDTH * C_HEIGHT];

int mouse_open(const char *dev_name)
{
	if(dev_name == NULL)
		dev_name = MICE_DEV;
	return open(dev_name, O_RDONLY);
}

mouse_event_t *mouse_parse(char buf[8], mouse_event_t *mevent)
{
	static mouse_event_t bakup;

	if(mevent == NULL)
		mevent = &bakup;
	switch(buf[0] & 0x7){
	case 1:
		mevent->button = 1;
		break;
	case 2: 
		mevent->button = 2;
		break;
	case 4:
		mevent->button = 3;
		break;
	default:
		mevent->button = 0;
	}	
	mevent->x = (unsigned)buf[1];
	mevent->y = -((unsigned)buf[2]);

	return mevent;
}

void cursor_save(const fb_info_t *fb, int x, int y)
{
	u32_t *s; int i, j;
	u32_t color;

	s = (u32_t *)fb->fb_buf;
	for(i = 0; i < C_HEIGHT; i++)
		for(j = 0; j < C_WIDTH; j++){
			color = s[(y + i) * fb->x_res + x + j];
			cursor_saver[i * C_WIDTH + j] = color;
		}
}

void cursor_restore(const fb_info_t *fb, int x, int y)
{
	u32_t *s; int i, j;
	u32_t color;

	s = (u32_t *)fb->fb_buf;
	for(i = 0; i < C_HEIGHT; i++)
		for(j = 0; j < C_WIDTH; j++){
			color = cursor_saver[i * C_WIDTH + j];
			s[(y + i) * fb->x_res + x + j] = color;
		}
}

void cursor_draw(const fb_info_t *fb, int x, int y)
{
	u32_t *s; int i, j;
	u32_t color;

	cursor_save(fb, x, y);
	
	s = (u32_t *)fb->fb_buf;
	for(i = 0; i < C_HEIGHT; i++)
		for(j = 0; j < C_WIDTH; j++){
			color = cursor[i * C_WIDTH + j];
			if(color != T___)
				s[(y + i) * fb->x_res + x + j] = color;
		}
}

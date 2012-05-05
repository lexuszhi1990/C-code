#ifndef MOUSE_H_
#define MOUSE_H_

#include "types.h"

#define C_WIDTH  10
#define C_HEIGHT 17
#define T___     0XFFFFFFFF
#define BORD     0x0
#define X___     0xFFFF

#define MICE_DEV "/dev/input/mice"

typedef struct
{
	int x;
	int y;
	int button;
}mouse_event_t;

extern int mouse_open(const char *dev_name);
extern mouse_event_t *mouse_parse(char buf[8], mouse_event_t *mevent);
extern void cursor_save(const fb_info_t *fb, int x, int y);
extern void cursor_restore(const fb_info_t *fb, int x, int y);
extern void cursor_draw(const fb_info_t *fb, int x, int y);

#endif

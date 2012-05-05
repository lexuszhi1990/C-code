#2011.2

DIR =
TARGET_DIR =

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = $(TARGET_DIR)main

CC = gcc
CFLAGS = -g -D_XOPEN_SOURCE=600 -c -Iinclude -I../jpeg-8/ -I../freetype-2.3.11/include
LDFLAGS = -lpthread -L../jpeg-8/.libs/ -ljpeg -L../freetype-2.3.11/objs/.libs -lfreetype 
DFLAGS = -DDEBUG -g

all: $(target)

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS) $(DFLAGS)
$(DIR)%.o:%.c
	$(CC) -o $@ $(CFLAGS) $< 
clean:
	rm -f $(target)
	rm -f $(obj)
	rm -f *~
	rm -f include/*~
.PHPNY: clean

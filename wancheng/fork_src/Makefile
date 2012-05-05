# By Panda.Guo at 2010-12-28

src = main.c fb.c display.c jpeg.c 

CC = gcc
LDFLAGS = -Wall -I../jpeg-8 -L../jpeg-8/.libs -ljpeg -static


main: $(src)
	$(CC) -o main $(src) $(LDFLAGS)

clean:
	-rm -f main
	-rm -f *~

#2011.1.16

DIR=
src=$(wildcard *.c)
obj=$(patsubst %.c, %.o, $(src))
target=$(DIR)main

CC=gcc
CFLAGS=-c -Wall
DFLAGS=-g -DDEBUG -Wall
LDFLAGS= -Wall

all: $(target)

$(target): $(obj)
	$(CC) $^ $(LDLAGS) -o $(@)
%.o: %.c 
	$(CC) $< $(CFLAGS) $(DFLAGS) -o $@
clean:
	rm -f $(target)
	rm -f $(obj)
	rm -f *~
.PHONY: clean

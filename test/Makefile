CC = gcc
DEFINE=
INCLUDE=
#CFLAGS=-g -Wall -Werror -pedantic-errors
CFLAGS=-Wall -Werror -pedantic-errors
LDFLAGS=

TARGET = hello func add


.PHONY: all
all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.o *~ $(TARGET)

CC=gcc
DEFINE=
INCLUDE=
CFLAGS=-g -Wall -Werror -pedantic-errors
LDFLAGS=
LIBS=
OBJS=main.o
TARGET=ycc

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

clean:
	rm -rf *.o *~ $(TARGET)



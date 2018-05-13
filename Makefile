CC=gcc
CFLAGS=-std=c11 -g -Wall -Werror -pedantic-errors
LDFLAGS=
LIBS=
DEFINE=
INCLUDE=
TARGET=ycc
SRCDIR=./src
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJDIR=./obj
OBJS=$(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
TESTDIR=./test

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

all: clean $(TARGET)

test: $(TARGET)
	./$(TARGET) $(TESTDIR)/hello.c

clean:
	rm -rf $(OBJDIR)/*.o *~ $(OBJDIR) $(TARGET)
	pushd test ; make clean ; popd




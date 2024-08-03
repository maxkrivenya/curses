CC=gcc
CFLAGS=-I.
DEPS 	= frame.h winsize.h node.h list.h
OBJ 	= main.o frame.o winsize.o node.o list.o
T_OBJ 	= test.o frame.o winsize.o node.o list.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
test: $(T_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

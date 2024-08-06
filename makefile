CC=gcc
CFLAGS=-I.
DEPS 	= ./src/headers/*.h
OBJ 	= main.o frame.o winsize.o node.o list.o defines.o ring.o fun_ctions.o framestack.o
T_OBJ 	= test.o frame.o winsize.o node.o list.o defines.o ring.o fun_ctions.o framestack.o


%.o: ./src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
test: $(T_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

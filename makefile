CC=gcc
CFLAGS=-I.
DEPS_H 	= src/headers/*.h
DEPS_O 	= frame.o winsize.o node.o list.o defines.o ring.o fun_ctions.o framestack.o
OBJ 	= main.o   $(DEPS_O)
T_OBJ 	= test.o   $(DEPS_O)
R_OBJ 	= reader.o $(DEPS_O)

%.o: ./src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test reader

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
test: $(T_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
reader: $(R_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

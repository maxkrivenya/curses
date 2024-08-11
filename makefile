CC=gcc
CFLAGS=-I.
DEPS_H 	= src/headers/*.h
DEPS_O 	= frame.o winsize.o node.o list.o defines.o ring.o fun_ctions.o framestack.o book.o

%.o: ./src/%.c $(DEPS_H)
	$(CC) -c -o $@ $< $(CFLAGS)
%.o: ./src/targets/%.c $(DEPS_H)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main test reader cards

main: main.o $(DEPS_O)
	$(CC) -o $@ $^ $(CFLAGS)
test: test.o $(DEPS_O)
	$(CC) -o $@ $^ $(CFLAGS)
reader: reader.o $(DEPS_O)
	$(CC) -o $@ $^ $(CFLAGS)
cards: cards.o $(DEPS_O)
	$(CC) -o $@ $^ $(CFLAGS)

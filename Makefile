CC=gcc
FLAGS=-Wall -Werror -c
BIN=bmp

all: $(BIN)

$(BIN): main.o bmp.o
	$(CC) main.o bmp.o -o $(BIN)

main.o: main.c
	$(CC) $(FLAGS) main.c

bmp.o: bmp.c bmp.h
	$(CC) $(FLAGS) bmp.c

clean:
	rm -f *.o $(BIN)

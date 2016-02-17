CC=gcc
FLAGS=-Wall -Werror -c -g -std=c99
BIN=bmp

all: $(BIN)

#$(BIN): main.o bmp.o bmp_rgbquad.o
#	$(CC) main.o bmp.o bmp_rgbquad.o -o $(BIN)
$(BIN): main.o bmp.o
	$(CC) main.o bmp.o -o $(BIN)

main.o: main.c
	$(CC) $(FLAGS) main.c

bmp.o: bmp.c bmp.h
	$(CC) $(FLAGS) bmp.c

#bmp_rgbquad.o: bmp_rgbquad.c bmp_rgbquad.h
#	$(CC) $(FLAGS) bmp_rgbquad.c

clean:
	rm -f *.o $(BIN)

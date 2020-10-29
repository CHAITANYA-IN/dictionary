CC=cc

CFLAGS=-c -Wall

all: solution # paragraph_file.txt stop_words_file.txt

solution: main.o AVL_main.o AVL_stop_words.o
	$(CC) main.o AVL_main.o AVL_stop_words.o -o solution

main.o: main.c
	$(CC) $(CFLAGS) main.c

AVL_main.o: ./Implementations/AVL_main.c
	$(CC) $(CFLAGS) ./Implementations/AVL_main.c

AVL_stop_words.o: ./Implementations/AVL_stop_words.c
	$(CC) $(CFLAGS) ./Implementations/AVL_stop_words.c

clean:
	rm -rf *.o solution
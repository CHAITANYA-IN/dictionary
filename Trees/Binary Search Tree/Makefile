CC=cc

CFLAGS=-c -Wall

all: solution # paragraph_file.txt stop_words_file.txt

solution: main.o BST_main.o BST_stop_words.o
	$(CC) main.o BST_main.o BST_stop_words.o -o solution

main.o: main.c
	$(CC) $(CFLAGS) main.c

BST_main.o: ./Implementations/BST_main.c
	$(CC) $(CFLAGS) ./Implementations/BST_main.c

BST_stop_words.o: ./Implementations/BST_stop_words.c
	$(CC) $(CFLAGS) ./Implementations/BST_stop_words.c

clean:
	rm -rf *.o solution
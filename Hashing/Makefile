all: solution

solution: dictionary.o main.o
	cc -Wall main.o dictionary.o -o solution

dictionary.o: dictionary.c
	cc -c dictionary.c -o dictionary.o

main.o: main.c
	cc -c main.c -o main.o

clean:
	rm *.o solution
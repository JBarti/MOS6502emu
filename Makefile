all:
	gcc -Wall -g -c ./lib/ram.c 
	gcc -Wall -g -c ./lib/bus.c 
	gcc -Wall -g -c ./lib/6502c.c
	gcc -Wall -g -o main main.c ram.o -lncurses
	gcc -Wall -g -o test test.c ram.o 6502c.o
	rm ./ram.o
	rm ./bus.o
run:
	./main

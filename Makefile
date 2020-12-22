all:
	gcc -Wall -g -c ./lib/ram.c 
	gcc -Wall -g -c ./lib/bus.c 
	gcc -Wall -g -o main main.c -lncurses

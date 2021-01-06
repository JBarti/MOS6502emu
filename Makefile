all:
	gcc -Wall -g -c ./lib/ram.c 
	gcc -Wall -g -c ./lib/bus.c 
	gcc -Wall -g -c ./lib/6502c.c
	gcc -Wall -g -c ./lib/6502c_utils.c
	gcc -Wall -g -c ./lib/6502c_opcodes.c
	gcc -Wall -g -c ./lib/6502c_addressing.c
	gcc -Wall -g -o main main.c ram.o bus.o 6502c.o 6502c_addressing.o 6502c_opcodes.o 6502c_utils.o -lncurses
	gcc -Wall -g -o test test.c ram.o bus.o 6502c.o 6502c_addressing.o 6502c_opcodes.o 6502c_utils.o
	rm ./ram.o
	rm ./bus.o
	rm ./6502c.o
	rm ./6502c_addressing.o
	rm ./6502c_opcodes.o
	rm ./6502c_utils.o

run:
	./main

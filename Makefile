all:
	gcc -Wall -g -c ./lib/ram.c 
	gcc -Wall -g -c ./lib/bus.c 
	gcc -Wall -g -c ./lib/6502c.c
	gcc -Wall -g -c ./lib/6502c_utils.c
	gcc -Wall -g -c ./lib/6502c_opcodes.c
	gcc -Wall -g -c ./lib/6502c_opcodes_utils.c
	gcc -Wall -g -c ./lib/6502c_addressing.c
	gcc -Wall -g -c ./lib/display_stdout.c
	gcc -Wall -g -c ./lib/display_cpu.c
	gcc -Wall -g -c ./lib/display_stat.c
	gcc -Wall -g -c ./lib/display_ram.c
	gcc -Wall -g -c ./lib/display_tree.c
	gcc -Wall -g -c ./lib/exec_tree.c
	gcc -Wall -g -c ./lib/exec_tree_utils.c
	gcc -Wall -g -o main main.c ram.o bus.o display_tree.o display_ram.o display_stat.o display_stdout.o display_cpu.o 6502c.o 6502c_addressing.o exec_tree.o exec_tree_utils.o 6502c_opcodes.o 6502c_opcodes_utils.o 6502c_utils.o -lncurses
	gcc -Wall -g -o test test.c ram.o bus.o exec_tree.o exec_tree_utils.o 6502c.o 6502c_addressing.o 6502c_opcodes.o 6502c_opcodes_utils.o 6502c_utils.o display_stdout.o -lncurses
	rm ./ram.o
	rm ./bus.o
	rm ./6502c.o
	rm ./6502c_addressing.o
	rm ./6502c_opcodes.o
	rm ./6502c_opcodes_utils.o
	rm ./6502c_utils.o
	rm ./display_stdout.o
	rm ./display_cpu.o
	rm ./display_stat.o
	rm ./display_ram.o
	rm ./exec_tree.o
	rm ./display_tree.o

run:
	gcc -Wall -g -o test test.c ram.o bus.o 6502c.o 6502c_addressing.o 6502c_opcodes.o 6502c_opcodes_utils.o 6502c_utils.o display_stdout.o
	./main

#include<string.h>
#include<stdio.h>

#include"../include/6502c.h"
#include"../include/bus.h"
#include"../include/ram.h"
#include"../include/display.h"

extern Iterator RAM_iter;
extern Iterator RAM_first;
extern Iterator RAM_stack;
extern Iterator RAM_instr;

extern CPU mainCPU;


byte readCPU(addr16 addr) {
    if(addr >= RAM_STACK_BEGIN && addr <= RAM_STACK_END) {
        byte val;
        RAM_stack = mem_read(RAM_stack, addr, &val);
        return val;
    }
    else if(addr >= 0x0000 && addr <= 0xffff) {
        byte val;
        RAM_iter = mem_read(RAM_iter, addr, &val);
        return val;
    }
}


void writeCPU(addr16 addr, byte data) {
    if(addr >= RAM_STACK_BEGIN && addr <= RAM_STACK_END) {
        RAM_stack = mem_write(RAM_stack, addr, data);
    }       
    else if(addr >= 0x0000 && addr <= 0xffff) {
        RAM_iter = mem_write(RAM_iter, addr, data);
    }       
}


void load_prg(char *filename) {
    FILE *prg = fopen(filename, "rb"); 
    addr16 addr_start = 0x0600;
    byte buff[1];
    
    while(!feof(prg)) {
        fread(buff, sizeof(byte), 1, prg);
        RAM_iter = mem_write(RAM_iter, addr_start, buff[0]);
        addr_start ++;
    }
}


void start_bus(char *filename) {
    initCPU(readCPU, writeCPU);
    mainCPU.PC = 0x0600; // Starting address of program counter
    load_prg(filename);
    displ_print("Program loaded\n");
}


void restart_bus() {
    initCPU(readCPU, writeCPU);
}


void tick() {
    byte opcode;
    RAM_instr = mem_read(RAM_instr, mainCPU.PC, &opcode);
    mainCPU.PC += 1;

    int len = instruction_len(opcode);


    byte args[2];
    for(int i=1; i<len; i++) {
        RAM_instr = mem_read(RAM_instr, mainCPU.PC, args + (i-1));
        mainCPU.PC += 1;
    }

    get_opcode_func(opcode)(opcode, args);
    displ_print_opcode("EXECUTED: %02x\n", opcode);
    displ_print_opcode("ARGA LEN: %d\n", len);
    displ_print_opcode("ARG 0: %02x\n", args[0]);
    displ_print_opcode("ARG 1: %02x\n", args[1]);
    
}

char *get_cpu_state() {
    static char buff[200];

    sprintf(
            buff, 
            "\
               A=$%02x X=$%02x Y=$%02x \n\
                SP=$%02x PC=$%04x \n\
                P=%hhu%hhu%hhu%hhu%hhu%hhu%hhu%hhu \n\
                  0CZIDBVN \
            ",
            mainCPU.A,
            mainCPU.X,
            mainCPU.Y,
            mainCPU.SP,
            mainCPU.PC,
            get_bit(mainCPU.status, 7),
            get_bit(mainCPU.status, 6),
            get_bit(mainCPU.status, 5),
            get_bit(mainCPU.status, 4),
            get_bit(mainCPU.status, 3),
            get_bit(mainCPU.status, 2),
            get_bit(mainCPU.status, 1),
            get_bit(mainCPU.status, 0)
            );
    
    return buff;
}

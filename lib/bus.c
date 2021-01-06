#include<stdio.h>

#include"../include/bus.h"
#include"../include/ram.h"
#include"../include/6502c.h"

extern Iterator RAM_iter;
extern Iterator RAM_first;
extern Iterator RAM_stack;

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


char *get_cpu_state() {
    char buff[100];

    sprintf(
            buff, 
            "\
                A=%02x X=%02x Y=%02x \n \
                SP=%02x PC=%04x \n \
                P=%c%c%c%c%c%c%c \n  \
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
    
    return strdup(buff);
}

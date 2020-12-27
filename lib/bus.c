#include"../include/bus.h"
#include"../include/ram.h"

extern Iterator RAM_iter;
extern  Iterator RAM_first;


byte readCPU(addr16 addr) {
    if(addr >= 0x0000 && addr <= 0xffff) {
        byte val;
        RAM_iter = mem_read(RAM_iter, addr, &val);
        return val;
    }
}


void writeCPU(addr16 addr, byte data) {
    if(addr >= 0x0000 && addr <= 0xffff) {
        RAM_iter = mem_write(RAM_iter, addr, data);
    }       
}

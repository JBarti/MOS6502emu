#include<ncurses.h>

#include"./include/ram.h"
#include"./include/6502c.h"

extern Iterator RAM_iter;
extern  Iterator RAM_first;
extern CPU mainCPU;


int main() {
    printf("#################\n");
    printf("#####RAM TEST####\n");
    printf("#################\n");
    printf("\n");
    
    RAM_iter = mem_write(RAM_iter, 0x0010, 0x01);
    RAM_iter = mem_write(RAM_iter, 0x0002, 0x02);
    RAM_iter = mem_write(RAM_iter, 0x0001, 0x03);
    print_memory(RAM_first);

    byte val = 0;
    RAM_iter =  mem_read(RAM_iter, 0x0010, &val);
    printf("%d\n", val);
    RAM_iter =  mem_read(RAM_iter, 0x0002, &val);
    printf("%d\n", val);
    RAM_iter =  mem_read(RAM_iter, 0x0102, &val);
    printf("%d\n", val);


    printf("#################\n");
    printf("#####CPU TEST####\n");
    printf("#################\n");
    printf("\n");

    mainCPU.status = 0b11110000;
    printf("%d\n", get_status_flag(NEGATIVE_FLAG));
    printf("%d\n", get_status_flag(INTERRUPT_DISABLE));
    set_status_flag(ZERO_FLAG, 0);
    set_status_flag(NEGATIVE_FLAG, 1);
    printf("%02x\n", mainCPU.status);


    printf("#################\n");
    printf("#####OVERFLOW####\n");
    printf("#################\n");
    printf("\n");
    
    int test_overflow = 0xff + 0x02;
    printf("%d\n", test_overflow);
    printf("%d\n", (byte)test_overflow);

    byte test_endian[2] = {0x34, 0x12};
    printf("%04x\n", le_to_be(test_endian));


    return 1;
}

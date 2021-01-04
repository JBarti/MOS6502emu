#include"../include/6502c.h"
#include<stdio.h>


CPU mainCPU = {
    0x00,
    0x00,
    0x00,

    0x00,
    0x00,

    0b00000000,
};


void initCPU(byte (*readbus)(addr16), void (*writebus)(addr16, byte)) {
    mainCPU.readbus = readbus;
    mainCPU.writebus = writebus;
}


byte get_status_flag(byte flag_pos) {
    return get_bit(mainCPU.status, flag_pos);
}


byte set_status_flag(byte flag_pos, byte value) {
    byte temp = 0b00000001;
    if(!value)
        mainCPU.status &=  ~(temp << flag_pos); 
    else if(value)
        mainCPU.status |=  (temp << flag_pos); 

    return mainCPU.status;
}






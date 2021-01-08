#include"../include/6502c.h"


CPU mainCPU = {
    .A=0x00,
    .X=0x00,
    .Y=0x00,

    .SP=STACK_END,
    .PC=0x0000,

    .status=0b00000000,

    .pullstack=stack_pull,
    .pushstack=stack_push,

    .readbus=NULL,
    .writebus=NULL,
};


void initCPU(byte (*readbus)(addr16), void (*writebus)(addr16, byte)) {
    mainCPU.A=0x00;
    mainCPU.X=0x00;
    mainCPU.Y=0x00;

   mainCPU.SP=STACK_END;
   mainCPU.PC=0x0000;

   mainCPU.status=0b00000000;

   mainCPU.pullstack=stack_pull;
   mainCPU.pushstack=stack_push;

   mainCPU.readbus=readbus;
   mainCPU.writebus=writebus;
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


byte stack_push(byte val) {
    mainCPU.writebus(0x0100 + mainCPU.SP, val);

    if(mainCPU.SP == STACK_BEGIN) {
        mainCPU.SP = STACK_END;
        printf("Stack write overflow %02x\n", mainCPU.SP);
    }
    else 
        mainCPU.SP -= 1;

    return val;
}


byte stack_pull() {
    byte val = mainCPU.readbus(0x0100 + mainCPU.SP);

    if(mainCPU.SP == STACK_END) {
        mainCPU.SP = STACK_BEGIN;
        printf("Stack read underflow %02x\n", mainCPU.SP);
    }
    else
        mainCPU.SP += 1;

    return val;
}

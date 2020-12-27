#include"../include/6502c.h"


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
    byte temp = 0b00000001;
    return !!(mainCPU.status & (temp << flag_pos));
}

byte set_status_flag(byte flag_pos, byte value) {
    byte temp = 0b00000001;
    if(value == 0)
        mainCPU.status &=  ~(temp << flag_pos); 
    else if(value == 1)
        mainCPU.status |=  (temp << flag_pos); 

    return mainCPU.status;
}


addr16 le_to_be(byte vals[2]) {  // little endian to big endian
    addr16 address = (vals[0] + (vals[1] << 8));
    return address;
}


byte ADC_util(byte opcode, byte val) {
    int temp = val + mainCPU.A + get_status_flag(CARRY_FLAG);
    
    if(temp > 255) 
        set_status_flag(CARRY_FLAG, 1);
    else 
        set_status_flag(CARRY_FLAG, 0);

    mainCPU.A = (byte)temp;

    return mainCPU.A;
}


void ADC(byte opcode, byte vals[2]) {
    switch(opcode) {
        case 0x69: // Immediate
            ADC_util(opcode, vals[0]);
            break;
        case 0x65: // Zero page
        {
            byte mem_val = mainCPU.readbus(vals[0]);
            ADC_util(opcode, mem_val);
            break;
        }
        case 0x75: // Absolute Page, X
        {
            byte mem_addr = mainCPU.X + vals[0];
            byte mem_val = mainCPU.readbus(mem_addr);
            ADC_util(opcode, mem_val);
        }
        case 0x6D: // Absolute
        {
            addr16 mem_addr = le_to_be(vals);
            byte mem_val = mainCPU.readbus(mem_addr);
            ADC_util(opcode, mem_val);
        }
        case 0x7D: // Absolute, X
        {
            addr16 mem_addr = le_to_be(vals) + mainCPU.X;
            byte mem_val = mainCPU.readbus(mem_addr);
            ADC_util(opcode, mem_val);
        }
    }
}

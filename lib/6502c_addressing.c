#include"../include/display.h"
#include"../include/6502c.h"


byte immediate(byte args[2], addr16 *val_addr) {
    return args[0];
}


byte zero_page(byte args[2], addr16 *val_addr) {
    byte mem_val = mainCPU.readbus(args[0]);
    *val_addr = args[0];
    return mem_val;
}


byte zero_page_x(byte args[2], addr16 *val_addr) {
        byte mem_addr = mainCPU.X + args[0];
        byte mem_val = mainCPU.readbus(mem_addr);
        *val_addr = mem_addr;
        return mem_val;
}


byte zero_page_y(byte args[2], addr16 *val_addr) {
        byte mem_addr = mainCPU.Y + args[0];
        byte mem_val = mainCPU.readbus(mem_addr);
        *val_addr = mem_addr;
        return mem_val;
}


byte absolute(byte args[2], addr16 *val_addr) {
    addr16 mem_addr = le_to_be(args[0], args[1]);
    byte mem_val = mainCPU.readbus(mem_addr);
    *val_addr = mem_addr;
    return mem_val;
}


byte abs_x(byte args[2], addr16 *val_addr) {
    addr16 mem_addr =  le_to_be(args[0], args[1]) + mainCPU.X;
    byte mem_val = mainCPU.readbus(mem_addr);
    *val_addr = mem_addr;
    return mem_val;
}


byte abs_y(byte args[2], addr16 *val_addr) {
    addr16 mem_addr = le_to_be(args[0], args[1]) + mainCPU.Y;
    byte mem_val = mainCPU.readbus(mem_addr);
    *val_addr = mem_addr;
    return mem_val;
}


byte indirect(byte args[2], addr16 *val_addr) {
    byte addr1 = le_to_be(args[0], args[1]);

    byte addr_lsb = mainCPU.readbus(addr1);
    byte addr_msb = mainCPU.readbus(addr1 + 1);

    *val_addr = le_to_be(addr_lsb, addr_msb);

    return 0;
}


byte indirect_x(byte args[2], addr16 *val_addr) {
    byte addr_lsb = args[0] + mainCPU.X;
    byte addr_msb = addr_lsb + 1;

    addr16 mem_addr = le_to_be(addr_lsb, addr_msb);
    byte mem_val = mainCPU.readbus(mem_addr); 

    *val_addr = mem_addr;

    return mem_val;
}


byte indirect_y(byte args[2], addr16 *val_addr) {
    byte carry = 0;

    byte addr1 = mainCPU.readbus(args[0]);
    byte addr_lsb = addc(addr1, mainCPU.Y, &carry);
    
    byte addr2 = mainCPU.readbus(args[0] + 1);
    byte addr_msb = addr2 + carry;

    addr16 mem_addr = le_to_be(addr_lsb, addr_msb);
    byte mem_val = mainCPU.readbus(mem_addr);

    *val_addr = mem_addr;

    return mem_val;
}


byte relative(byte args[2], addr16 *val_addr) {
    return (sbyte)args[0];  
}


byte implied(byte args[2], addr16 *val_addr) {
    return 0;
}


byte accumulator(byte args[2], addr16 *val_addr) {
    return 0;
}

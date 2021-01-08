#include"../include/6502c.h"


addr16 le_to_be(byte lsb, byte msb) {  // little endian to big endian
    addr16 address = (lsb + (msb << 8));
    return address;
}


byte get_lo(addr16 addr) {
    byte lo = (addr & 0x00ff);
    return lo;
}


byte get_hi(addr16 addr) {
    byte hi = (addr & 0xff00) >> 8;
    return hi;
}


byte addc(byte val1, byte val2, byte *carry) {
    int sum = val1 + val2;

    *carry = sum > 0xff;

    return (byte)sum;
}


void push_PC() {
    mainCPU.pushstack(get_hi(mainCPU.PC));
    mainCPU.pushstack(get_lo(mainCPU.PC));
}


void pull_PC() {
    byte PC_lo = mainCPU.pullstack();
    byte PC_hi = mainCPU.pullstack();
    mainCPU.PC = le_to_be(PC_lo, PC_hi);
}


byte ADC_util(byte val, byte add_opt) {
    int temp;
    if(add_opt == ADD_POSITIVE) {
        temp = val + mainCPU.A + get_status_flag(CARRY_FLAG);
    }
    else if(add_opt == ADD_NEGATIVE) {
        temp = val + mainCPU.A - (1 - get_status_flag(CARRY_FLAG));
    }

    byte sum = (byte)temp;

    set_status_flag(
            OVERFLOW_FLAG,
            (val ^ sum) & (mainCPU.A ^ sum) & 0x80
            );
    set_status_flag(CARRY_FLAG, temp > 0xff);
    set_status_flag(ZERO_FLAG, sum == 0x00);
    set_status_flag(NEGATIVE_FLAG, sum >= 0b10000000);

    mainCPU.A = sum;
    return mainCPU.A;
}


byte AND_util(byte val) {
    mainCPU.A &= val;

    set_status_flag(ZERO_FLAG, mainCPU.A == 0);
    set_status_flag(ZERO_FLAG, mainCPU.A >= 0b10000000);
    
    return mainCPU.A;
}


byte ASL_util(byte val) {
    set_status_flag(CARRY_FLAG, get_bit(val, 7));
    val <<= 1;
    set_status_flag(NEGATIVE_FLAG, get_bit(val, 7));
    return val;
}


byte BIT_util(byte val) {
    byte result = val & mainCPU.A;

    set_status_flag(ZERO_FLAG, result);
    set_status_flag(NEGATIVE_FLAG, get_bit(val, 7));
    set_status_flag(OVERFLOW_FLAG, get_bit(val, 6));

    return result;
}


void CP_util(byte res) {
    set_status_flag(CARRY_FLAG, res >= 0);
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(ZERO_FLAG, get_bit(res, 7));
}


sbyte CMP_util(byte val) {
    sbyte res = mainCPU.A - val;
    CP_util(res);
    return res;
}


sbyte CPX_util(byte val) {
    sbyte res = mainCPU.X - val;
    CP_util(res);
    return res;
}


sbyte CPY_util(byte val) {
    sbyte res = mainCPU.Y - val;
    CP_util(res);
    return res;
}


byte EOR_util(byte val) {
    byte res = mainCPU.A ^ val;

    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(res, 7));

    return res;
}


byte LD_util(byte val, byte *reg) {
    set_status_flag(ZERO_FLAG, !!val);
    set_status_flag(ZERO_FLAG, get_bit(val, 7));
    *reg = val;

    return *reg;
}


byte LSR_util(byte val) {
    set_status_flag(CARRY_FLAG, get_bit(val, 0));

    val >>= 1;

    set_status_flag(ZERO_FLAG, val == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(val, 7));
    
    return val;
}


byte ORA_util(byte val) {
    mainCPU.A |= val;

    set_status_flag(ZERO_FLAG, mainCPU.A == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.A, 7));

    return mainCPU.A;
}


byte ROL_util(byte val) {
    byte res = (val << 1) + get_status_flag(CARRY_FLAG);

    set_status_flag(CARRY_FLAG, get_bit(val, 7));
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(res, 7));

    return res;
}


byte ROR_util(byte val) {
    byte res = (val >> 1) + (get_status_flag(CARRY_FLAG) << 7);

    set_status_flag(CARRY_FLAG, get_bit(val, 0));
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(res, 7));

    return res;
}

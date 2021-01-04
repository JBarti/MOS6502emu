#include"../include/6502c.h"
#include<stdio.h>


addr16 le_to_be(byte lsb, byte msb) {  // little endian to big endian
    addr16 address = (lsb + (msb << 8));
    return address;
}


byte addc(byte val1, byte val2, byte *carry) {
    int sum = val1 + val2;

    *carry = sum > 0xff;

    return (byte)sum;
}


byte ADC_util(byte val) {
    int temp = val + mainCPU.A + get_status_flag(CARRY_FLAG);
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
    set_status_flag(CARRY_FLAG, val >= 0b10000000);

    val <<= 1;

    return val;
}


byte BIT_util(byte val) {
    byte result = val & mainCPU.A;

    set_status_flag(ZERO_FLAG, result);
    set_status_flag(NEGATIVE_FLAG, get_bit(result, 7));
    set_status_flag(OVERFLOW_FLAG, get_bit(result, 6));

    return result;
}


sbyte CMP_util(byte val) {
    sbyte res = mainCPU.A - val;

    set_status_flag(CARRY_FLAG, res >= 0);
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(ZERO_FLAG, get_bit(res, 7));

    return res;
}


sbyte CPX_util(byte val) {
    sbyte res = mainCPU.X - val;

    set_status_flag(CARRY_FLAG, res >= 0);
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(ZERO_FLAG, get_bit(res, 7));

    return res;
}


sbyte CPY_util(byte val) {
    sbyte res = mainCPU.Y - val;

    set_status_flag(CARRY_FLAG, res >= 0);
    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(res, 7));

    return res;
}


byte EOR_util(byte val) {
    byte res = mainCPU.A ^ val;

    set_status_flag(ZERO_FLAG, res == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(res, 7));

    return res;
}

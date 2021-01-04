#include"../include/6502c.h"
#include<stdio.h>



void ADC(byte opcode, byte args[2]) { // Add with carry
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x69: // Immediate 
            val = immediate(args);
            break;
        case 0x65: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x75: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x6D: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x7D: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0x79: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0x61: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0x71: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for ADC %02x\n", opcode);
            return;
    }

    ADC_util(val);
    printf("STATUS: %02x\n", mainCPU.status);
}


void AND(byte opcode, byte args[2]) { // Logical AND
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x29: // Immediate 
            val = immediate(args);
            break;
        case 0x25: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x35: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x2D: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x3D: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0x39: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0x21: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0x31: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for AND %02x\n", opcode);
            return;
    }

    AND_util(val);
}


void ASL(byte opcode, byte args[2]) { // Arytmetic shift left
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x0A: // Accumulator
            mainCPU.A = ASL_util(mainCPU.A);
            break;
        case 0x06: // Zero Page
        {
            val = zero_page(args, &val_addr);
            mainCPU.writebus(val_addr, ASL_util(val));
            break;
        }
        case 0x16: // Zero Page, X
        {
            val = zero_page_x(args, &val_addr);
            mainCPU.writebus(val_addr, ASL_util(val));
            break;
        }
        case 0x0E: // Absolute
        {
            val = absolute(args, &val_addr);
            mainCPU.writebus(val_addr, ASL_util(val));
            break;
        }
        default:
            printf("Unrecognized opcode for ASL %02x\n", opcode);
            return;
    }
}


void BCC(byte opcode, byte args[2]) { // Branch if carry clear
    if(opcode != 0x90) {
        printf("Unrecognized opcode for BCC %02x\n", opcode);
        return;
    }

    if(get_status_flag(CARRY_FLAG))
        mainCPU.PC += relative(args);
}


void BEQ(byte opcode, byte args[2]) { // Branch if equal
    if(opcode != 0xf0) {
        printf("Unrecognized opcode for BEQ %02x\n", opcode);
        return;
    }

    if(get_status_flag(ZERO_FLAG))
        mainCPU.PC += relative(args);
}


void BIT(byte opcode, byte args[2]) { // Bit test
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x24: // Zero Page
        {
            val = zero_page(args, &val_addr);
        }
        case 0x2c: // Absolute
        {
            val = absolute(args, &val_addr);
        }
        default:
        {
            printf("Unrecognized opcode for BIT %02x\n", opcode);
            return;
        }
    }  

    BIT_util(val);
}


void BMI(byte opcode, byte args[2]) { // Branch if minus
    if(opcode != 0x30) {
        printf("Unrecognized opcode for BMI %02x\n", opcode);
        return;
    }

    if(get_status_flag(NEGATIVE_FLAG))
        mainCPU.PC += relative(args);
}


void BNE(byte opcode, byte args[2]) { // Branch if not equal
    if(opcode != 0xd0) {
        printf("Unrecognized opcode for BNE %02x\n", opcode);
        return;
    }

    if(!get_status_flag(ZERO_FLAG))
        mainCPU.PC += relative(args);
}


void BPL(byte opcode, byte args[2]) { // Branch if positive
    if(opcode != 0x10) {
        printf("Unrecognized opcode for BPL %02x\n", opcode);
        return;
    } 

    if(!get_status_flag(NEGATIVE_FLAG))
        mainCPU.PC += relative(args);
}


void BRK(byte opcode, byte args[2]) { // Force interupt
    // Requires stack and interupt vector
}


void BVC(byte opcode, byte args[2]) { // Branch if overflow clear
    if(opcode != 0x50){
        printf("Unrecognized opcode for BVC %02x\n", opcode);
        return;
    }

    if(!get_status_flag(OVERFLOW_FLAG))
        mainCPU.PC += relative(args);
}


void BVS(byte opcode, byte args[2]) { // Branch if overflow set
    if(opcode != 0x70) {
        printf("Unrecognized opcode for BVS %02x\n", opcode);
        return;
    }

    if(get_status_flag(OVERFLOW_FLAG))
        mainCPU.PC += relative(args);
}


void CLC(byte opcode, byte args[2]) { // Clear carry flag
    if(opcode != 0x18) {
        printf("Unrecognized opcode for CLC %02x\n", opcode);
        return;
    }

    set_status_flag(CARRY_FLAG, 0);
}


void CLD(byte opcode, byte args[2]) { // Clear decimal mode
    if(opcode != 0xd8) {
        printf("Unrecognized opcode for CLD %02x\n", opcode);
        return;
    }

    set_status_flag(DECIMAL_MODE, 0);
}


void CLI(byte opcode, byte args[2]) { // Clear interrupt disable
    if(opcode != 0x58){
        printf("Unrecognized opcode for CLI %02x\n", opcode);
        return;
    }

    set_status_flag(INTERRUPT_DISABLE, 0);
}


void CLV(byte opcode, byte args[2]) { // Clear overflow flag
    if(opcode != 0xb8) {
        printf("Unrecognized opcode for CLV %02x\n", opcode);
        return;
    }

    set_status_flag(OVERFLOW_FLAG, 0);
}


void CMP(byte opcode, byte args[2]) { // Compare
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xc9: // Immediate 
            val = immediate(args);
            break;
        case 0xc5: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0xd5: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0xcd: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0xdd: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0xd9: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0xc1: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0xd1: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for CMP %02x\n", opcode);
            return;
    }

    CMP_util(val);
}


void CPX(byte opcode, byte args[2]) { // Compare X register
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xe0:
            val = immediate(args);
            break;
        case 0xe4:
            val = zero_page(args, &val_addr);
            break;
        case 0xec:
            val = absolute(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for CPX %02x\n", opcode);
            return;
    }

    CPX_util(val);
}


void CPY(byte opcode, byte args[2]) { // Compare Y register
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xe0:
            val = immediate(args);
            break;
        case 0xe4:
            val = zero_page(args, &val_addr);
            break;
        case 0xec:
            val = absolute(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for CPY %02x\n", opcode);
            return;
    }

    CPY_util(val);
}


void DEC(byte opcode, byte args[2]) { // Decrement memory
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xc6:
            val = zero_page(args, &val_addr);
            break;
        case 0xd6:
            val = zero_page_x(args, &val_addr);
            break;
        case 0xce:
            val = absolute(args, &val_addr);
            break;
        case 0xde:
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for DEC %02x\n", opcode);
            return;
    }

    set_status_flag(ZERO_FLAG, val-1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((val - 1), 7));

    mainCPU.writebus(val_addr, val-1);
}


void DEX(byte opcode, byte args[2]) { // Decrement X register
    if(opcode != 0xca) {
        printf("Unrecognized opcode for DEX %02x\n", opcode);
        return;
    } 

    set_status_flag(ZERO_FLAG, mainCPU.X-1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((mainCPU.X - 1), 7));

    mainCPU.X -= 1;
}


void DEY(byte opcode, byte args[2]) { // Decrement Y register
    if(opcode != 0x88) {
        printf("Unrecognized opcode for DEY %02x\n", opcode);
        return;
    }

    set_status_flag(ZERO_FLAG, mainCPU.Y-1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((mainCPU.Y - 1), 7));

    mainCPU.Y -= 1;
}


void EOR(byte opcode, byte args[2]) { // Exclusive OR
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x49:
            val = immediate(args);
            break;
        case 0x45:
            val = zero_page(args, &val_addr);
            break;
        case 0x55:
            val = zero_page_x(args, &val_addr);
            break;
        case 0x4D:
            val = absolute(args, &val_addr);
            break;
        case 0x5D:
            val = abs_x(args, &val_addr);
            break;
        case 0x59:
            val = abs_y(args, &val_addr);
            break;
        case 0x41:
            val = indirect_x(args, &val_addr);
            break;
        case 0x51:
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for EOR %02x\n", opcode);
            return;
    }

    EOR_util(val);
}


void INC(byte opcode, byte args[2]) { // Increment memory
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xe6:
            val = zero_page(args, &val_addr);
            break;
        case 0xf6:
            val = zero_page_x(args, &val_addr);
            break;
        case 0xee:
            val = absolute(args, &val_addr);
            break;
        case 0xfe:
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for INC %02x\n", opcode);
            return;
    }

    set_status_flag(ZERO_FLAG, val+1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((val + 1), 7));

    mainCPU.writebus(val_addr, val+1);
    
}


void INX(byte opcode, byte args[2]) { // Increment X register
    if(opcode != 0xe8) {
        printf("Unrecognized opcode for INX %02x\n", opcode);
        return;
    } 

    set_status_flag(ZERO_FLAG, mainCPU.X+1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((mainCPU.X + 1), 7));

    mainCPU.X += 1;
}


void INY(byte opcode, byte args[2]) { // Increment Y register
    if(opcode != 0xc8) {
        printf("Unrecognized opcode for INY %02x\n", opcode);
        return;
    }

    set_status_flag(ZERO_FLAG, mainCPU.Y+1 == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit((mainCPU.Y + 1), 7));

    mainCPU.Y -= 1;
}


void JMP(byte opcode, byte args[2]) { // Jump
    byte val;
    addr16 val_addr;
    
    switch(opcode) {
        case 0x4c:
            val = absolute(args, &val_addr);
            break;
        case 0x6c:
            val = 
    }
}

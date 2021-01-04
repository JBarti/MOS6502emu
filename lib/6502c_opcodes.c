#include"../include/6502c.h"
#include<stdio.h>

// Unfinished: JSR, BRK

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
            set_status_flag(ZERO_FLAG, mainCPU.A == 0);
            return;
        case 0x06: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x16: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x0E: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x1E: // Absolute X
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for ASL %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, ASL_util(val));
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
    addr16 val_addr;

    switch(opcode) {
        case 0x4c:
            absolute(args, &val_addr);
            break;
        case 0x6c:
            indirect(args, &val_addr); 
    }

    mainCPU.PC = val_addr;
}


void JSR(byte opcode, byte args[2]) { // Jump to subroutine
    // Implement after implementing stack
}


void LDA(byte opcode, byte args[2]) { // Load accumulator
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xa9: // Immediate 
            val = immediate(args);
            break;
        case 0xa5: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0xb5: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0xad: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0xbd: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0xb9: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0xa1: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0xb1: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for LDA %02x\n", opcode);
            return;
    }

    LD_util(val, &mainCPU.A);
}


void LDX(byte opcode, byte args[2]) { // Load X register
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xa2: // Immediate 
            val = immediate(args);
            break;
        case 0xa6: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0xb6: // Zero Page, Y
            val = zero_page_y(args, &val_addr);
            break;
        case 0xae: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0xbe: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for LDX %02x\n", opcode);
            return;
    }

    LD_util(val, &mainCPU.X);
}


void LDY(byte opcode, byte args[2]) { // Load X register
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xa0: // Immediate 
            val = immediate(args);
            break;
        case 0xa4: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0xb4: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0xac: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0xbc: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for LDY %02x\n", opcode);
            return;
    }

    LD_util(val, &mainCPU.Y);
}


void LSR(byte opcode, byte args[2]) { // Logical shift right
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x4a: // Accumulator
            mainCPU.A = ASL_util(mainCPU.A);
            return;
        case 0x46: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x56: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x4e: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x5e: // Absolute X
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for LSR %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, LSR_util(val));
}


void NOP(byte opcode, byte args[2]) { // No operation
    if(opcode != 0xea) {
        printf("Unrecognized opcode for NOP %02x\n", opcode);
        return;
    }
}


void ORA(byte opcode, byte args[2]) { // Logical inclusive OR
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x09: // Immediate 
            val = immediate(args);
            break;
        case 0x05: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x15: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x0d: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x1d: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0x19: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0x01: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0x11: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for ORA %02x\n", opcode);
            return;
    }

    ORA_util(val);
}


void PHA(byte opcode, byte args[2]) { // Push accumulator to stack
    if(opcode != 0x48) {
        printf("Unrecognized opcode for PHA %02x\n", opcode);
        return;
    }

    mainCPU.pushstack(mainCPU.A);
}


void PHP(byte opcode, byte args[2]) { // Push processor status to stack
    if(opcode != 0x08) {
        printf("Unrecognized opcode for PHP %02x\n", opcode);
        return;
    }

    mainCPU.pushstack(mainCPU.status);
}


void PLA(byte opcode, byte args[2]) { // Pull stack into accumulator
    if(opcode != 0x68) {
        printf("Unrecognized opcode for PLA %02x\n", opcode);
        return;
    }

    mainCPU.A = mainCPU.pullstack();
    set_status_flag(ZERO_FLAG, mainCPU.A == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.A, 7));
}


void PLP(byte opcode, byte args[2]) { // Pull stack into status
    if(opcode != 0x28) {
        printf("Unrecognized opcode for PLP %02x\n", opcode);
        return;
    }

    mainCPU.status = mainCPU.pullstack();
}


void ROL(byte opcode, byte args[2]) { // Rotate left
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x2a: // Accumulator
            mainCPU.A = ROL_util(mainCPU.A);
            return;
        case 0x26: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x36: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x2e: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x3e: // Absolute X
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for ROL %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, ROL_util(val));
}


void ROR(byte opcode, byte args[2]) { // Rotate right
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0x6a: // Accumulator
            mainCPU.A = ROL_util(mainCPU.A);
            return;
        case 0x66: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0x76: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0x2e: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0x3e: // Absolute X
            val = abs_x(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for ROR %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, ROR_util(val));
}


void RTI(byte opcode, byte args[2]) { // Return from interrupt
    if(opcode != 0x40) {
        printf("Unrecognized opcode for RTI %02x\n", opcode);
        return;
    }

    mainCPU.status = mainCPU.pullstack();
    mainCPU.PC = mainCPU.pullstack();
}


void RTS(byte opcode, byte args[2]) { // Return from subroutine
    // TODO: should probably be tested
    if(opcode != 0x60) {
        printf("Unrecognized opcode for RTS %02x\n", opcode);
        return;
    }

    mainCPU.PC = mainCPU.pullstack();
}


void SBC(byte opcode, byte args[2]) { // Subtract with carry
    byte val;
    addr16 val_addr;

    switch(opcode) {
        case 0xe9: // Immediate 
            val = immediate(args);
            break;
        case 0xe5: // Zero Page
            val = zero_page(args, &val_addr);
            break;
        case 0xf5: // Zero Page, X
            val = zero_page_x(args, &val_addr);
            break;
        case 0xeD: // Absolute
            val = absolute(args, &val_addr);
            break;
        case 0xfD: // Absolute, X
            val = abs_x(args, &val_addr);
            break;
        case 0xf9: // Absolute, Y
            val = abs_y(args, &val_addr);
            break;
        case 0xe1: // (Indirect, X)
            val = indirect_x(args, &val_addr);
            break;
        case 0xf1: // (Indirect), Y
            val = indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for SBC %02x\n", opcode);
            return;
    }

    // Because subtraction is the same as addition with the two's complement
    ADC_util(~val + 1);
}


void SEC(byte opcode, byte args[2]) { // Set carry flag
    if(opcode != 0x38) {
        printf("Unrecognized opcode for SEC %02x\n", opcode);
        return;
    }

    set_status_flag(CARRY_FLAG, 1);
}


void SED(byte opcode, byte args[2]) { // Set decimal flag
    if(opcode != 0x38) {
        printf("Unrecognized opcode for SED %02x\n", opcode);
        return;
    }
    
    set_status_flag(DECIMAL_MODE, 1);
}


void SEI(byte opcode, byte args[2]) { // Set interrupt disable
    if(opcode != 0x38) {
        printf("Unrecognized opcode for SEI %02x\n", opcode);
        return;
    }

    set_status_flag(INTERRUPT_DISABLE, 1);
}


void STA(byte opcode, byte args[2]) { // Store accumulator
    addr16 val_addr;

    switch(opcode) {
        case 0x85: // Zero Page
            zero_page(args, &val_addr);
            break;
        case 0x95: // Zero Page, X
            zero_page_x(args, &val_addr);
            break;
        case 0x8d: // Absolute
            absolute(args, &val_addr);
            break;
        case 0x9d: // Absolute, X
            abs_x(args, &val_addr);
            break;
        case 0x99: // Absolute, Y
            abs_y(args, &val_addr);
            break;
        case 0x81: // (Indirect, X)
            indirect_x(args, &val_addr);
            break;
        case 0x91: // (Indirect), Y
            indirect_y(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for STA %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, mainCPU.A);
}


void STX(byte opcode, byte args[2]) { // Store X register
    addr16 val_addr;

    switch(opcode) {
        case 0x86: // Zero Page
            zero_page(args, &val_addr);
            break;
        case 0x96: // Zero Page, Y
            zero_page_y(args, &val_addr);
        case 0x8e: // Absolute
            absolute(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for STX %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, mainCPU.X);
}


void STY(byte opcode, byte args[2]) { // Store Y register
    addr16 val_addr;

    switch(opcode) {
        case 0x84: // Zero Page
            zero_page(args, &val_addr);
            break;
        case 0x94: // Zero Page, X
            zero_page_x(args, &val_addr);
        case 0x8c: // Absolute
            absolute(args, &val_addr);
            break;
        default:
            printf("Unrecognized opcode for STY %02x\n", opcode);
            return;
    }

    mainCPU.writebus(val_addr, mainCPU.Y);
}


void TAX(byte opcode, byte args[2]) { // Transfer accumulator to Y
    if(opcode != 0xaa) {
        printf("Unrecognized opcode for TAX %02x\n", opcode);
        return;
    }

    mainCPU.X = mainCPU.A;
    set_status_flag(ZERO_FLAG, mainCPU.X == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.Y, 7));
}


void TAY(byte opcode, byte args[2]) { // Transfer accumulator to Y
    if(opcode != 0xa8) {
        printf("Unrecognized opcode for TAY %02x\n", opcode);
        return;
    }

    mainCPU.Y = mainCPU.A;
    set_status_flag(ZERO_FLAG, mainCPU.Y == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.Y, 7));
}


void TSX(byte opcode, byte args[2]) { // Transfer stack pointer to X
    if(opcode != 0xba) {
        printf("Unrecognized opcode for TSX %02x\n", opcode);
        return;
    }
    
    mainCPU.X = mainCPU.SP;
    set_status_flag(ZERO_FLAG, mainCPU.X == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.X, 7));
}


void TXA(byte opcode, byte args[2]) { // Transfer X to accumulator
    if(opcode != 0x8a) {
        printf("Unrecognized opcode for TXA %02x\n", opcode);
        return;
    }

    mainCPU.A = mainCPU.X;
    set_status_flag(ZERO_FLAG, mainCPU.A == 0);
    set_status_flag(NEGATIVE_FLAG, get_bit(mainCPU.A, 7));
}


void TXS(byte opcode, byte args[2]) { // Transfer X to stack pointer
}

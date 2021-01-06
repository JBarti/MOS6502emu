#include"../include/6502c.h"


int instruction_len(byte opcode) {
    switch(opcode) {
        case 0x65: return 2; 
        case 0x75: return 2;
        case 0x6D: return 3;
        case 0x7D: return 3;
        case 0x79: return 3;
        case 0x61: return 2;
        case 0x71: return 2;
        case 0x29: return 2;
        case 0x25: return 2;
        case 0x35: return 2;
        case 0x2D: return 3;
        case 0x3D: return 3;
        case 0x39: return 3;
        case 0x21: return 2;
        case 0x31: return 2;
        case 0x0A: return 1;
        case 0x06: return 2;
        case 0x16: return 2;
        case 0x0E: return 3;
        case 0x1E: return 3;
        case 0x90: return 2;
        case 0xB0: return 2;
        case 0xF0: return 2;
        case 0x24: return 2;
        case 0x2C: return 3;
        case 0x30: return 2;
        case 0xD0: return 2;
        case 0x10: return 2;
        case 0x00: return 1;
        case 0x50: return 2;
        case 0x70: return 2;
        case 0x18: return 1;
        case 0xD8: return 1;
        case 0x58: return 1;
        case 0xB8: return 1;
        case 0xC9: return 2;
        case 0xC5: return 2;
        case 0xD5: return 2;
        case 0xCD: return 3;
        case 0xDD: return 3;
        case 0xD9: return 3;
        case 0xC1: return 2;
        case 0xD1: return 2;
        case 0xE0: return 2;
        case 0xE4: return 2;
        case 0xEC: return 3;
        case 0xC0: return 2;
        case 0xC: return 2;
        case 0xCC: return 3;
        case 0xC6: return 2;
        case 0xD6: return 2;
        case 0xCE: return 3;
        case 0xDE: return 3;
        case 0xCA: return 1;
        case 0x88: return 1;
        case 0x49: return 2;
        case 0x45: return 2;
        case 0x55: return 2;
        case 0x4D: return 3;
        case 0x5D: return 3;
        case 0x59: return 3;
        case 0x41: return 2;
        case 0x51: return 2;
        case 0xE6: return 2;
        case 0xF6: return 2;
        case 0xEE: return 3;
        case 0xFE: return 3;
        case 0xE8: return 1;
        case 0xC8: return 1;
        case 0x4C: return 3;
        case 0x6C: return 3;
        case 0x20: return 3;
        case 0xA9: return 2;
        case 0xA5: return 2;
        case 0xB5: return 2;
        case 0xAD: return 3;
        case 0xBD: return 3;
        case 0xB9: return 3;
        case 0xA1: return 2;
        case 0xB1: return 2;
        case 0xA2: return 2;
        case 0xA6: return 2;
        case 0xB6: return 2;
        case 0xAE: return 3;
        case 0xBE: return 3;
        case 0xA0: return 2;
        case 0xA4: return 2;
        case 0xB4: return 2;
        case 0xAC: return 3;
        case 0xBC: return 3;
        case 0x4A: return 1;
        case 0x46: return 2;
        case 0x56: return 2;
        case 0x4E: return 3;
        case 0x5E: return 3;
        case 0xEA: return 1;
        case 0x09: return 2;
        case 0x05: return 2;
        case 0x15: return 2;
        case 0x0D: return 3;
        default: 
       {
           printf("Opcode not found %02x\n", opcode);
           return 0;
       }
    }
}

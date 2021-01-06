// Status flag positions
#define CARRY_FLAG 6
#define ZERO_FLAG 5
#define INTERRUPT_DISABLE 4
#define DECIMAL_MODE 3
#define BREAK_CMD 2
#define OVERFLOW_FLAG 1
#define NEGATIVE_FLAG 0

#define STACK_BEGIN 0x00
#define STACK_END 0xff

#define ADD_NEGATIVE 0
#define ADD_POSITIVE 1

#define get_bit(val, pos) !!(val & (0b00000001 << pos))

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short addr16;
typedef struct _6502c CPU;

struct _6502c {
    byte A;
    byte X;
    byte Y;
    
    byte SP;
    addr16 PC;

    byte status; // | 0 | C | Z | I | D | B | V | N |

    byte (*pullstack)();
    byte (*pushstack)(byte val);

    byte (*readbus)(addr16); 
    void (*writebus)(addr16, byte);
};

CPU mainCPU;

// General utils
void initCPU(byte (*readbus)(addr16), void (*writebus)(addr16, byte));
byte get_status_flag(byte flag_pos);
byte set_status_flag(byte flag_pos, byte value);
addr16 le_to_be(byte lsb, byte msb);
byte get_lo(addr16 addr);
byte get_hi(addr16 addr);
byte stack_push(byte val);
byte stack_pull();
void push_PC();
void pull_PC();

//Opcode utils
int instruction_len(byte opcode);

// Opcodes
void ADC(byte opcode, byte args[2]);
void AND(byte opcode, byte args[2]);
void ASL(byte opcode, byte args[2]);
void BCC(byte opcode, byte args[2]);
void BCS(byte opcode, byte args[2]); 
void BEQ(byte opcode, byte args[2]); 
void BIT(byte opcode, byte args[2]); 
void BMI(byte opcode, byte args[2]); 
void BNE(byte opcode, byte args[2]); 
void BPL(byte opcode, byte args[2]); 
void BRK(byte opcode, byte args[2]); 
void BVC(byte opcode, byte args[2]); 
void BVS(byte opcode, byte args[2]); 
void CLC(byte opcode, byte args[2]); 
void CLD(byte opcode, byte args[2]); 
void CLI(byte opcode, byte args[2]); 
void CLV(byte opcode, byte args[2]); 
void CMP(byte opcode, byte args[2]); 
void CPX(byte opcode, byte args[2]); 
void CPY(byte opcode, byte args[2]); 
void DEC(byte opcode, byte args[2]); 
void DEX(byte opcode, byte args[2]); 
void DEY(byte opcode, byte args[2]); 
void EOR(byte opcode, byte args[2]); 
void INC(byte opcode, byte args[2]); 
void INX(byte opcode, byte args[2]); 
void INY(byte opcode, byte args[2]); 
void JMP(byte opcode, byte args[2]); 
void JSR(byte opcode, byte args[2]); 
void LDA(byte opcode, byte args[2]); 
void LDX(byte opcode, byte args[2]); 
void LDY(byte opcode, byte args[2]); 
void LSR(byte opcode, byte args[2]); 
void NOP(byte opcode, byte args[2]); 
void ORA(byte opcode, byte args[2]); 
void PHA(byte opcode, byte args[2]); 
void PHP(byte opcode, byte args[2]); 
void PLA(byte opcode, byte args[2]); 
void PLP(byte opcode, byte args[2]); 
void ROL(byte opcode, byte args[2]); 
void ROR(byte opcode, byte args[2]); 
void RTI(byte opcode, byte args[2]); 
void RTS(byte opcode, byte args[2]); 
void SBC(byte opcode, byte args[2]); 
void SEC(byte opcode, byte args[2]); 
void SED(byte opcode, byte args[2]); 
void SEI(byte opcode, byte args[2]); 
void STA(byte opcode, byte args[2]); 
void STX(byte opcode, byte args[2]); 
void STY(byte opcode, byte args[2]); 
void TAX(byte opcode, byte args[2]); 
void TAY(byte opcode, byte args[2]); 
void TSX(byte opcode, byte args[2]); 
void TXA(byte opcode, byte args[2]); 
void TXS(byte opcode, byte args[2]); 
void TYA(byte opcode, byte args[2]); 

// Opcode utils
byte ADC_util(byte val, byte add_opt);
byte AND_util(byte val);
byte ASL_util(byte val);
byte BIT_util(byte val);
sbyte CMP_util(byte val);
sbyte CPX_util(byte val);
sbyte CPY_util(byte val);
byte EOR_util(byte val);
byte LD_util(byte val, byte *reg);
byte LSR_util(byte val);
byte ORA_util(byte val);
byte ROL_util(byte val);
byte ROR_util(byte val);

// Addressing modes
byte addc(byte val1, byte val2, byte *carry);
byte immediate(byte args[2]);
byte zero_page(byte args[2], addr16 *val_addr);
byte zero_page_x(byte args[2], addr16 *val_addr);
byte zero_page_y(byte args[2], addr16 *val_addr);
byte absolute(byte args[2], addr16 *val_addr);
byte abs_x(byte args[2], addr16 *val_addr);
byte abs_y(byte args[2], addr16 *val_addr);
void indirect(byte args[2], addr16 *val_addr);
byte indirect_x(byte args[2], addr16 *val_addr);
byte indirect_y(byte args[2], addr16 *val_addr);
sbyte relative(byte args[2]);

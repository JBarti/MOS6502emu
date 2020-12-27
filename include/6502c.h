#define CARRY_FLAG 6
#define ZERO_FLAG 5
#define INTERRUPT_DISABLE 4
#define DECIMAL_MODE 3
#define BREAK_CMD 2
#define OVERFLOW_FLAG 1
#define NEGATIVE_FLAG 0

typedef unsigned char byte;
typedef unsigned short addr16;
typedef struct _6502c CPU;

struct _6502c {
    byte A;
    byte X;
    byte Y;
    
    byte SP;
    byte PC;

    byte status; // | 0 | C | Z | I | D | B | V | N |

    byte (*readbus)(addr16); 
    void (*writebus)(addr16, byte);
};

CPU mainCPU;

void initCPU(byte (*readbus)(addr16), void (*writebus)(addr16, byte));
byte get_status_flag(byte flag_pos);
byte set_status_flag(byte flag_pos, byte value);
addr16 le_to_be(byte vals[2]);
void ADC(byte opcode, byte vals[2]); // Add with carry

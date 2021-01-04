// The bus implements methods for reading and writing to certain addresses. 
// It then calls devices mapped to them.

#define STACK_BEGIN 0x0100
#define STACK_END 0x01ff

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short addr16;

byte readCPU(addr16 addr);
void writeCPU(addr16 addr, byte data);
void tick();

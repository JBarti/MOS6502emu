// The bus implements methods for reading and writing to certain addresses. 
// It then calls devices mapped to them.


typedef unsigned char byte;
typedef unsigned short addr16;

byte readCPU(addr16 addr);
void writeCPU(addr16 addr, byte data);
void tick();

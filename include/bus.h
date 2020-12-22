// The bus implements methods for reading and writing to certain addresses. 
// It then calls devices mapped to them.


typedef unsigned char byte;

byte readCPU(byte addr);
void writeCPU(byte addr, byte data);
void tick();

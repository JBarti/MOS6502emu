// Ram will be emulated using a double linked sorted list with an iterator.
// The iterator is pointing at the last accessed memory register. 
// The value of a register not present in the list will be treated as zero.

#define MAX_ADDR 0xffff
#define foreach(t, r) for(t=r; t != NULL; t=t->after)

typedef struct _register Register;
typedef struct _register *Iterator;

typedef unsigned short addr16;
typedef unsigned char byte;

Register *RAM_iter;

struct _register {
    addr16 address; 
    byte val;
    Register *after;
    Register *before;
};


Register *create_register(addr16 address, byte val);
Iterator create_iterator(Register *from);
Iterator mem_write(Iterator iter, addr16 address, byte val);
Iterator mem_read(Iterator iter, addr16 address, byte *valptr);
void print_memory(Register *first);

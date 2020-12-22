// Ram will be emulated using a double linked sorted list with an iterator.
// The iterator is pointing at the last accessed memory register. 
// The value of a register not present in the list will be treated as zero.


typedef struct _register Register;
typedef struct _register Iterator;

typedef unsigned short addr16;
typedef unsigned char byte;

struct _register {
    addr16 address; 
    byte val;
    Register *after;
    Register *before;
};


Register *create_register(addr16 address, byte val);
Register *insert_after(Iterator *iter, addr16 address, byte val);
Iterator *create_iterator(Register *from);
Iterator *insert_element(Iterator *iter, addr16 address, byte val);

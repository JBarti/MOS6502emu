#include<stdio.h>
#include<stdlib.h>

#include"../include/ram.h"

Register RAM = {
    0x0000,
    0x00,
    NULL,
    NULL
};

Iterator RAM_iter = &RAM;
Iterator RAM_stack = &RAM;
Iterator RAM_first = &RAM;


Register *create_register(addr16 address, byte val) {
    Register *new = (Register *)malloc(sizeof(Register));

    if(new == NULL) { 
        printf("Error: failed to allocate memory for register\n");
        exit(1);
    }

    new->address = address;
    new->val = val;
    new->after = NULL; 
    new->before = NULL;

    return new;
}


Iterator create_iterator(Register *from) {
    return &RAM;
}


Iterator insert_after(Iterator iter, addr16 address, byte val) {
    Register *new = create_register(address, val);

    if(iter->after == NULL) { 
        new->before = iter;
        iter->after = new; 

        return new;
    }

    new->before = iter;
    new->after = iter->after;

    iter->after->before = new;
    iter->after = new;

    return new;
}


Iterator insert_before(Iterator iter, addr16 address, byte val) {
    Register *new = create_register(address, val);

    if(iter->before == NULL) {
        new->after = iter;
        iter->before = new;

        return new;
    }

    new->after = iter;
    new->before = iter->before;

    iter->before->after = new;
    iter->before = new;

    return new;
}


Iterator mem_write(Iterator iter, addr16 address, byte val) {
    if(address > iter->address) { 
        if(iter->after == NULL || address < iter->after->address) { 
            return insert_after(iter, address, val);
        }
        else {
            return mem_write(iter->after, address, val);
        }
    }
    else if(address < iter->address) {
        if(iter->before == NULL || address > iter->before->address) {
            return insert_before(iter, address, val);
        }
        else {
            return mem_write(iter->before, address, val);
        }
    }

    iter->val = val;
    return iter;
}


Iterator mem_read(Iterator iter, addr16 address, byte *valptr) {
    if(address > iter->address) { 
        if(iter->after == NULL || address < iter->after->address) { 
            *valptr = 0x00; 
            return iter;
        }
        else {
            return mem_read(iter->after, address, valptr);
        }
    }
    else if(address < iter->address) {
        if(iter->before == NULL || address > iter->before->address) {
            *valptr = 0x00; 
            return iter;
        }
        else {
            return mem_read(iter->before, address, valptr);
        }
    }

    *valptr = iter->val; 
    return iter;
}


void print_memory(Register *first) {
    Iterator iter = create_iterator(first);

    printf("ADDR \t VAL\n");
    foreach(iter, first) {
        printf("0x%04x\t0x%02x\n", iter->address, iter->val);
    } 
}


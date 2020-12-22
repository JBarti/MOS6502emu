#include<stdio.h>
#include<stdlib.h>

#include"../include/ram.h"

const Register *RAM = create_register(0x0000, 0x00);

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


Iterator *create_iterator(Register *from) {
    Iterator *iter = from;
    return iter;
}


Iterator *insert_element(Iterator *iter, addr16 address, byte val) {
    if(address > iter->address) { 
        if(iter->after == NULL) { 
            iter->after = create_register(address, val); 
            return iter->after;
        }
        else if(address < iter->after->address) {
            Register *new = create_register(address, val);
            new->before = iter;
            new->after = iter->after;

            iter->after->before = new;
            iter->after = new;

            return new;
        }
        else {
            return insert_element(iter->after, address, val);
        }
    }
    else if(address < iter->address) {
        if(iter->before == NULL) {
            iter->before = create_register(address, val);
            return iter->before;
        }
        else if(address > iter->before->address) {
            Register *new = create_register(address, val);

            new->after = iter;
            new->before = iter->before;

            iter->before->after = new;
            iter->before = new;
        }
        else {
            return insert_element(iter->before, address, val);
        }
    }

    printf("Error: can't insert register\n");
    return iter;
}


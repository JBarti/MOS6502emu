#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/exec_tree.h"
#include"../include/6502c.h"


char *get_addressing_name(byte (*addressing)(byte*, addr16*)) {
    char buff[30] = "";

    if(addressing == immediate) { strcat(buff, "immediate") ; }
    else if(addressing == implied) { strcat(buff, "implied"); }
    else if(addressing == zero_page) { strcat(buff, "zero_page"); }
    else if(addressing == zero_page_x) { strcat(buff, "zero_page_x") ; }
    else if(addressing == zero_page_y) { strcat(buff, "zero_page_y"); }
    else if(addressing == absolute) { strcat(buff, "absolute") ; }
    else if(addressing == abs_x) { strcat(buff, "abs_x"); }
    else if(addressing == abs_y) {  strcat(buff, "abs_y"); }
    else if(addressing == indirect) { strcat(buff, "indirect"); }
    else if(addressing == indirect_x) { strcat(buff, "indirect_x"); }
    else if(addressing == indirect_y) {  strcat(buff, "indirect_y"); }
    else if(addressing == relative) {  strcat(buff, "relative"); }
    
    return strdup(buff);
}


ExecNodeList *create_list(ExecNode *val) {
    ExecNodeList *list = (ExecNodeList *)malloc(sizeof(ExecNodeList));
    if(list == NULL) {
        printf("Cannot allocate memory for ExecNodeList\n");
        exit(1);
    }

    list->val = val;
    list->next = NULL;

    return list;
}


ExecNodeList *list_push(ExecNodeList *root, ExecNode *val) {
    ExecNodeList *new_node = create_list(val); 
    ExecNodeList *last = root;

    while(last->next != NULL) { last = last->next; }
    last->next = new_node;

    return root;
}


ExecNode *find_by_index(ExecNodeList *list_root, addr16 index) {
    ExecNodeList *temp;
    foreach_list(list_root, temp) {
        if(temp->val->index == index) { return temp->val; }
    }

    return NULL;
}


void print_args(byte *args, int opc_len) {
    if(opc_len == 2) {
        printf("Args: 0x%02x\n", args[0]);
    }
    else if(opc_len == 3) {
        printf("Args: 0x%04x\n", le_to_be(args[0], args[1]));
    }

}


void print_node(ExecNode *node) {
        printf("Index: %d\n", node->index);
        printf("Opcode: 0x%02x\n", node->opcode);
        printf("Name: %s\n", node->name);
        printf("Command length: %d\n", node->cmd_len);
        printf("Addressing mode: %s\n", node->addressing_mode_name);
        print_args(node->args, node->cmd_len);
}


char *get_node_data(ExecNode *node) {
    char buff[500];
    

    sprintf(buff, "Index: %d\n", node->index);
    sprintf(buff, "Opcode: 0x%02x\n", node->opcode);
    sprintf(buff, "Name: %s\n", node->name);
    sprintf(buff, "Command length: %d\n", node->cmd_len);
    sprintf(buff, "Addressing mode: %s\n", node->addressing_mode_name);

    int opc_len = node->cmd_len;
    if(opc_len == 2) {
        sprintf(buff, "Args: 0x%02x\n", node->args[0]);
    }
    else if(opc_len == 3) {
        sprintf(buff, "Args: 0x%04x\n", le_to_be(node->args[0], node->args[1]));
    }
    return buff;
}


void print_exec_list(ExecNodeList *root) {
    ExecNodeList *temp;

    foreach_list(root, temp) {
        print_node(temp->val);
        printf("#######################################\n");
    }
}

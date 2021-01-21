#include<stdio.h>

#define foreach_list(head, temp) for(temp=head->next; temp!=NULL; temp=temp->next)

typedef struct _exec_node ExecNode;
typedef struct _exec_node_list ExecNodeList;

typedef unsigned char byte;
typedef unsigned short addr16;


struct _exec_node { 
    addr16 index;
    byte opcode;
    char *name;
    byte *args;
    int cmd_len;
    char *addressing_mode_name;
    byte (*addressing_mode)(byte*, addr16*);
    ExecNode *yes;
    ExecNode *no;
};


struct _exec_node_list {
    ExecNode *val;
    ExecNodeList *next;
};


byte *get_opcode_args(FILE *fp, int opc_len);

ExecNode *build_tree(char *filename);
ExecNode *get_jmp_node(ExecNode *jmp_cmd);
ExecNode *build_tree_util(ExecNodeList *list_root, ExecNodeList *curr_cmd, ExecNode *tree_root);
ExecNode *get_exec_node(FILE *fp, byte opcode);
ExecNode *find_by_index(ExecNodeList *list_root, addr16 index);

ExecNodeList *create_list(ExecNode *val);
ExecNodeList *list_push(ExecNodeList *root, ExecNode *val);

void print_exec_list(ExecNodeList *root);
void print_tree(ExecNode *tree_root);
void print_node(ExecNode *node);

char *get_node_data(ExecNode *node);
char *get_addressing_name(byte (*addressing)(byte*, addr16*));

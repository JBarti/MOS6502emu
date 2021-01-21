#include<stdio.h>
#include<stdlib.h>
#include"../include/exec_tree.h"
#include"../include/6502c.h"


void print_tree(ExecNode *tree_root) {
    if(tree_root == NULL) { return; }
    print_node(tree_root);
    printf("#############################\n");
    print_tree(tree_root->yes);
}


ExecNode *allocate_exec_node() {
    static byte args_none[2] = {0, 0};

    ExecNode *node = (ExecNode *)malloc(sizeof(ExecNode));
    if(node == NULL) {
        printf("Cannot allocate memory for ExecNode\n");
        exit(1);
    }

    node->index = 0xffff;
    node->opcode = 0xff;
    node->name = "Unknown";
    node->args = args_none;
    node->cmd_len = 0;
    node->addressing_mode_name = "Unknown";
    node->addressing_mode = NULL;
    node->yes = NULL;
    node->no = NULL;

    return node;
}


ExecNode *get_exec_node(FILE *fp, byte opcode) {
        static addr16 index = 0x0600;

        char *opc_name = get_opcode_name(opcode);
        int opc_len = instruction_len(opcode);
        byte (*addressing)(byte*, addr16*) = get_opcode_addressing(opcode);
        char *addressing_name = get_addressing_name(addressing);
        byte *opc_args = get_opcode_args(fp, opc_len - 1);
        ExecNode *node = allocate_exec_node();


        node->opcode = opcode;
        node->name = opc_name;
        node->args = opc_args;
        node->cmd_len = opc_len;
        node->addressing_mode_name = addressing_name;
        node->addressing_mode = addressing;
        node->yes = NULL;
        node->no = NULL;
        node->index = index;

        index += opc_len;

        return node;
}


ExecNode *get_jmp_node(ExecNode *jmp_cmd) {
    ExecNode *node = allocate_exec_node();
    node->name = "Unknown jump";

    if(jmp_cmd->addressing_mode == absolute) {
        addr16 mem_addr = le_to_be(jmp_cmd->args[0], jmp_cmd->args[1]);
        node->index = mem_addr;
    }

    return node;
}


ExecNode *get_return_node(ExecNode *return_cmd) {
    ExecNode *node = allocate_exec_node();
    node->name = "Unknown return";

    return node;
}


ExecNode *get_branch_node(ExecNodeList *list_root, ExecNode *branch_cmd) {
    addr16 index = branch_cmd->index + (sbyte)branch_cmd->args[0] + 2;
    ExecNode *node = find_by_index(list_root, index);
    return node;
}


ExecNode *build_tree_util(ExecNodeList *list_root, ExecNodeList *curr_cmd, ExecNode *tree_root) {
    if(curr_cmd == NULL) {
        return tree_root;
    } 

    int is_jump = is_opcode_jump(curr_cmd->val->opcode);
    
    switch(is_jump) {
        case NOT_JUMP_OP:
            tree_root->yes = build_tree_util(list_root, curr_cmd->next, curr_cmd->val);
            break;
        case BRANCH_OP:
            tree_root->yes = build_tree_util(list_root, curr_cmd->next, curr_cmd->val);
            tree_root->yes->no = get_branch_node(list_root, curr_cmd->val);
            break;
        case JUMP_OP:
        case SR_JUMP_OP:
            return get_jmp_node(curr_cmd->val);
            break;
        case RETURN_OP:
            return get_return_node(curr_cmd->val);
            break;
        default:
            printf("This should not happen");
    }

    return tree_root;
}


byte *get_opcode_args(FILE *fp, int args_len) {
    byte *buff = (byte *)malloc(sizeof(byte) * args_len);
    fread(buff, sizeof(byte), args_len, fp);

    return buff;
}


ExecNode *build_tree(char *filename) {
    FILE *prg = fopen(filename, "rb"); 
    ExecNodeList *exec_list_root = create_list(NULL);
    byte buff[1];
    
    while(!feof(prg)) {
        fread(buff, sizeof(byte), 1, prg);
        ExecNode *exec_node = get_exec_node(prg, *buff);
        list_push(exec_list_root, exec_node);
    }

    fclose(prg);

    if(exec_list_root->next == NULL) {
        printf("Progam not loaded\n");
        return NULL;
    }

    ExecNode *tree_root = exec_list_root->next->val;
    build_tree_util(exec_list_root, exec_list_root->next->next, tree_root);

    return tree_root;
}

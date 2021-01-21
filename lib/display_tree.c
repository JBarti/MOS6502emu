#include"../include/display.h"
#include"../include/exec_tree.h"
#include"../include/6502c.h"

ExecNode *tree_root = NULL;

WINDOW *create_win_tree(int max_rows, int max_cols, char *filename) {
    WINDOW *win = newwin(
            max_rows/2 - 1,
            max_cols/2,
            max_rows/2,
            0
            );
    
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Execution tree");
    refresh();
    wrefresh(win);

    tree_root = build_tree(filename);

    TREE_WIN = win;

    return win;
}

void display_node(ExecNode *node, int start_y, int start_x) {

    if(node == NULL) {
        mvwprintw(TREE_WIN, start_y, start_x, "NULL");
        return;
    }

    mvwprintw(TREE_WIN, start_y, start_x, "Index: %d\n", node->index);
    mvwprintw(TREE_WIN, start_y+1, start_x, "Opcode: 0x%02x\n", node->opcode);
    mvwprintw(TREE_WIN, start_y+2, start_x, "Name: %s\n", node->name);
    mvwprintw(TREE_WIN, start_y+3, start_x, "Command length: %d\n", node->cmd_len);
    mvwprintw(TREE_WIN, start_y+4, start_x, "Addressing mode: %s\n", node->addressing_mode_name);

    int opc_len = node->cmd_len;
    if(opc_len == 2) {
        mvwprintw(TREE_WIN, start_y+5, start_x, "Args: 0x%02x\n", node->args[0]);
    }
    else if(opc_len == 3) {
        mvwprintw(TREE_WIN, start_y+5, start_x, "Args: 0x%04x\n", le_to_be(node->args[0], node->args[1]));
    }
}


void display_tree() {
    werase(TREE_WIN);
    mvwprintw(TREE_WIN, 0, 1, "Execution tree");
    display_node(tree_root, 2, 10);

    if(tree_root != NULL) {
        display_node(tree_root->yes, 11, 2);
        display_node(tree_root->no, 11, 30);
    }

    mvwprintw(TREE_WIN, 10, 2, "--NON COND-- (x)");
    mvwprintw(TREE_WIN, 10, 30, "--COND-- (c)");

    box(TREE_WIN, 0, 0);
    refresh();
    wrefresh(TREE_WIN);
}


void tree_next(int pos_next) {
    if(tree_root == NULL) {
        return;
    }
    if(pos_next == TREE_NON_COND) {
        tree_root = tree_root->yes;
    }
    else if(pos_next == TREE_COND) {
        tree_root = tree_root->no;
    }

    display_tree();
}


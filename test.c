#include"./include/exec_tree.h"


int main() {
    ExecNode *nd = build_tree("./tests/test1.bin");
    print_tree(nd);
    printf("Addressing mode: %s\n", nd->addressing_mode_name);
    return 1;
}

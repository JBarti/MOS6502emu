#include<ncurses.h>

WINDOW *STDOUT_WIN;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short addr16;

WINDOW *create_win_stdout(int max_rows, int max_cols);
void displ_print(char *msg);
void displ_print_opcode(char *msg, byte fmt);

#include<ncurses.h>

WINDOW *STDOUT_WIN;

WINDOW *create_win_stdout(int max_rows, int max_cols);
void displ_print(char *msg);

#include"../include/display.h"

WINDOW *create_win_stdout(int max_rows, int max_cols) {
    WINDOW *win = newwin(
            (max_rows - max_rows/4) - 1, 
            max_cols/2 , 
            max_rows/4, 
            max_cols/2
            );

    box(win, 0, 0);
    scrollok(win, 1);
    refresh();
    wrefresh(win);

    STDOUT_WIN = win;
    return win;
}


void displ_print(char *msg) {
    wprintw(STDOUT_WIN, msg);
    box(STDOUT_WIN, 0, 0);
    refresh();
    wrefresh(STDOUT_WIN);
}

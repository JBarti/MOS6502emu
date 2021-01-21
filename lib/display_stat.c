#include"../include/display.h"


WINDOW *create_win_stat(int max_rows, int max_cols) {
    WINDOW *win = newwin(1, max_cols, max_rows-1, 0);
    refresh();
    wrefresh(win);
    
    STAT_WIN = win;

    return win;
}


void show_key_press(char key) {
    wmove(STAT_WIN, 0, COLS-4);
    wclrtoeol(STAT_WIN);
    mvwprintw(STAT_WIN, 0, COLS-3, &key);
    refresh();
    wrefresh(STAT_WIN);
}

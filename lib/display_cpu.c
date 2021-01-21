#include"../include/display.h"


WINDOW *create_win_CPU(int max_rows, int max_cols) {
    WINDOW *win = newwin(max_rows/4, max_cols/2, 0, max_cols/2);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "CPU display");
    refresh();
    wrefresh(win);

    CPU_WIN = win;

    return win;
}


void show_CPU_stat(char *cpu_state) {
    werase(CPU_WIN);
    mvwprintw(CPU_WIN, 3, 1, cpu_state);
    box(CPU_WIN, 0, 0);
    mvwprintw(CPU_WIN, 0, 1, "CPU display");
    refresh();
    wrefresh(CPU_WIN);
}

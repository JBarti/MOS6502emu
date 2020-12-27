#include<ncurses.h>
#include<string.h>

#include"./include/ram.h"

#define MAX_MEM_COLS 16

extern Iterator RAM_iter;
extern  Iterator RAM_first;


int *show_RAM_util(WINDOW *RAM_win, int index, byte val) {
    static int col = 1;
    static int row = 0;
    
    col = index % MAX_MEM_COLS * 3 + 9;
    row += (index % MAX_MEM_COLS) == 0;

    if(index % MAX_MEM_COLS == 0) {
        mvwprintw(RAM_win, row, 1, "0x%04x", index);
    }
    mvwprintw(RAM_win, row, col, "%02x", val);

    return &row;
}


void show_RAM(WINDOW *RAM_win) {
    int *rowptr;
    for(int i=0x0000; i<0x0100; i++) {
        byte val;
        RAM_iter = mem_read(RAM_iter, i, &val);
        rowptr = show_RAM_util(RAM_win, i, val);
    }

    *rowptr += 1;

    for(int i=0x8000; i<0x8100; i++) {
        byte val;
        RAM_iter = mem_read(RAM_iter, i, &val);
        rowptr = show_RAM_util(RAM_win, i, val);
    }

    wrefresh(RAM_win);
}


WINDOW *create_win_RAM(int max_rows, int max_cols) {
    WINDOW *win = newwin(max_rows, 16*2+25, 0, 0);

    box(win, 0, 0);
    mvwprintw(win, 0, 1, "RAM display");
    refresh();
    wrefresh(win);

    return win;
}


int main() {
    WINDOW *win_root = initscr();
    cbreak(); //Stop buffering of typed characters by TTY
    noecho(); //Stop echoing of typed characters
    curs_set(0); //Hide the cursor from the screen
    
    int rows, cols;
    getmaxyx(win_root, rows, cols);

    RAM_iter = mem_write(RAM_iter, 0x0050, 0xff);
    WINDOW *RAM_win = create_win_RAM(rows, cols);
    show_RAM(RAM_win);

    getch();
    delwin(RAM_win);
    endwin();
}

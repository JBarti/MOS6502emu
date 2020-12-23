#include<ncurses.h>
#include<stdio.h>

#include"./include/ram.h"

extern Iterator RAM_iter;
extern  Iterator RAM_first;

int main() {
    WINDOW *win = initscr();
    cbreak(); //Stop buffering of typed characters by TTY
    noecho(); //Stop echoing of typed characters
    
    printw("MAIN WINDOW");

    WINDOW *subwindow = newwin(10, 100, 0, 0);

    refresh();
    box(subwindow,0,0);
    mvwprintw(subwindow, 1, 1, "SUBWINDOW");

    refresh();
    wrefresh(subwindow);


    getch();
    delwin(subwindow);
    endwin();
}

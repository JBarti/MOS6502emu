#include<ncurses.h>
#include<stdlib.h>
#include<stdio.h>

#include"./include/ram.h"
#include"./include/bus.h"
#include"./include/display.h"

#define MAX_MEM_COLS 15

#define MAX_PAGES 257 
#define PAGE_SIZE 255
#define NEXT_PAGE 0
#define PREV_PAGE 1
#define CURR_PAGE 2

extern Iterator RAM_iter;
extern  Iterator RAM_first;

WINDOW *RAM_WIN;
WINDOW *ROOT_WIN;
WINDOW *STAT_WIN;
WINDOW *CPU_WIN;

int ROWS, COLS;


void show_RAM_util(int index, byte val, int **rowptr, int **colptr) {
    static int col = 1;
    static int row = 0;
    
    col = (index % MAX_MEM_COLS) * 3 + 9;
    row += (index % MAX_MEM_COLS) == 0;

    if(index % MAX_MEM_COLS == 0) {
        mvwprintw(RAM_WIN, row, 1, "0x%04x", index);
    }
    mvwprintw(RAM_WIN, row, col, "%02x", val);

    *colptr = &col;
    *rowptr = &row;
}


void show_RAM(byte move_opt) {
    static int page = 1;
    int *rowptr, *colptr;
    
    if(move_opt == NEXT_PAGE) {
        if(page == MAX_PAGES) { page = 1; }
        else { page +=1; }
    }

    if(move_opt == PREV_PAGE) {
        if(page == 1) { page = MAX_PAGES; }
        else { page -=1; }
    }

    werase(RAM_WIN);
    box(RAM_WIN, 0, 0);
    mvwprintw(RAM_WIN, 0, 1, "RAM display");

    for(int i=(page-1)*PAGE_SIZE; i<page*PAGE_SIZE; i++) {
        byte val;
        RAM_iter = mem_read(RAM_iter, i, &val);
        show_RAM_util(i, val, &rowptr, &colptr);
    }

    *colptr = 1;
    *rowptr = 0;

    wrefresh(RAM_WIN);
}


WINDOW *create_win_RAM(int max_rows, int max_cols) {
    WINDOW *win = newwin(max_rows-1, max_cols/2, 0, 0);

    box(win, 0, 0);
    mvwprintw(win, 0, 1, "RAM display");
    refresh();
    wrefresh(win);

    return win;
}


WINDOW *create_win_stat(int max_rows, int max_cols) {
    WINDOW *win = newwin(1, max_cols, max_rows-1, 0);
    refresh();
    wrefresh(win);
    
    return win;
}


WINDOW *create_win_CPU(int max_rows, int max_cols) {
    WINDOW *win = newwin(max_rows/4, max_cols/2, 0, max_cols/2);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "CPU display");
    refresh();
    wrefresh(win);

    return win;
}

void show_key_press(char key){
    wmove(STAT_WIN, 0, COLS-4);
    wclrtoeol(STAT_WIN);
    mvwprintw(STAT_WIN, 0, COLS-3, &key);
    refresh();
    wrefresh(STAT_WIN);
}


void show_CPU_stat() {
    werase(CPU_WIN);
    mvwprintw(CPU_WIN, 3, 1, get_cpu_state());
    box(CPU_WIN, 0, 0);
    mvwprintw(CPU_WIN, 0, 1, "CPU display");
    refresh();
    wrefresh(CPU_WIN);
}
    

void key_press(char key) {
    show_key_press(key);

    switch(key){
        case 'q':
            delwin(RAM_WIN);
            endwin();
            exit(EXIT_SUCCESS);
        case 'l':
            show_RAM(NEXT_PAGE);
            break;
        case 'h':
            show_RAM(PREV_PAGE);
            break;
        case 'n':
            tick();
            show_CPU_stat();
            break;
    }
}


int main() {
    newterm(NULL, stderr, stdin);
    ROOT_WIN = stdscr;
    cbreak(); // Stop buffering of typed characters by TTY
    noecho(); // Stop echoing of typed characters
    curs_set(0); // Hide the cursor from the screen

    getmaxyx(ROOT_WIN, ROWS, COLS);
    create_win_stdout(ROWS, COLS);

    start_bus("./tests/test1.bin");
    
    RAM_WIN = create_win_RAM(ROWS, COLS);
    show_RAM(CURR_PAGE);

    STAT_WIN = create_win_stat(ROWS, COLS);
    CPU_WIN = create_win_CPU(ROWS, COLS);
    show_CPU_stat();

    char key;
    while(1) {
        key = getch();
        key_press(key);
    }

    return 1;
}

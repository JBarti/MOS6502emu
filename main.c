#include<ncurses.h>
#include<stdlib.h>
#include<stdio.h>

#include"./include/bus.h"
#include"./include/display.h"


extern WINDOW *STDOUT_WIN;
extern WINDOW *RAM_WIN;
extern WINDOW *CPU_WIN;
extern WINDOW *STAT_WIN;
extern WINDOW *TREE_WIN;

WINDOW *ROOT_WIN;

int ROWS, COLS;
    

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
            show_CPU_stat(get_cpu_state());
            break;
        case 'x':
            tree_next(TREE_NON_COND);
            break;
        case 'c':
            tree_next(TREE_COND);
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
    
    create_win_RAM(ROWS, COLS);
    show_RAM(CURR_PAGE);

    create_win_stat(ROWS, COLS);

    create_win_CPU(ROWS, COLS);
    show_CPU_stat(get_cpu_state());

    create_win_tree(ROWS, COLS, "./tests/test1.bin");
    display_tree();



    char key;
    while(1) {
        key = getch();
        key_press(key);
    }

    return 0;
}

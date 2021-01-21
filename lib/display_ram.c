#include"../include/display.h"
#include"../include/ram.h"


extern Iterator RAM_iter;
extern  Iterator RAM_first;


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
    WINDOW *win = newwin(max_rows/2, max_cols/2, 0, 0);

    box(win, 0, 0);
    mvwprintw(win, 0, 1, "RAM display");
    refresh();
    wrefresh(win);

    RAM_WIN = win;

    return win;
}

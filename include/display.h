#include<ncurses.h>

#define MAX_MEM_COLS 15
#define MAX_PAGES 257 
#define PAGE_SIZE 255

#define NEXT_PAGE 0
#define PREV_PAGE 1
#define CURR_PAGE 2

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short addr16;

WINDOW *STDOUT_WIN;
WINDOW *RAM_WIN;
WINDOW *CPU_WIN;
WINDOW *STAT_WIN;
WINDOW *TREE_WIN;

void displ_print(char *msg);
void displ_print_opcode(char *msg, byte fmt);
WINDOW *create_win_stdout(int max_rows, int max_cols);

void show_RAM_util(int index, byte val, int **rowptr, int **colptr);
void show_RAM(byte move_opt);
WINDOW *create_win_RAM(int max_rows, int max_cols);

void show_key_press(char key);
WINDOW *create_win_stat(int max_rows, int max_cols);

void show_CPU_stat(char *cpu_state);
WINDOW *create_win_CPU(int max_rows, int max_cols);

void display_tree();
WINDOW *create_win_tree(int max_rows, int max_cols, char *filename);

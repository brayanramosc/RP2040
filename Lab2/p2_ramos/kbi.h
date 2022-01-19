#ifndef _KBI_H
#define _KBI_H

// 4x4 keyboard
#define ROW1 0
#define ROW2 1
#define ROW3 2
#define ROW4 3
#define COL1 4
#define COL2 5
#define COL3 6
#define COL4 7

extern volatile bool key_pressed;

void kbi_init();
void set_rows_as_input();
void set_rows_as_output();
char get_key();

#endif

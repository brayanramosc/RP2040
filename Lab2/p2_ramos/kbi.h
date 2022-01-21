#ifndef _KBI_H
#define _KBI_H

// 4x4 keyboard
#define ROW1 7
#define ROW2 6
#define ROW3 5
#define ROW4 4
#define COL1 3
#define COL2 2
#define COL3 1
#define COL4 0

extern volatile bool key_pressed;

void kbi_init();
void set_rows_as_input();
void set_rows_as_output();
char get_key();

#endif

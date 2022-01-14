#ifndef _KBI_H
#define _KBI_H

// 4x4 keyboard
#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
#define COL1 5
#define COL2 6
#define COL3 7
#define COL4 8

#define DEBOUNCE_MS 50

extern volatile bool key_pressed;

void kbi_init();
void set_rows_as_input();
void set_rows_as_output();

#endif

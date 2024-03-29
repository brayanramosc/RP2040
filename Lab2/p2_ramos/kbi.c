#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "kbi.h"
#include "events.h"

// Characters for a 4x4 keyboard
char keys[4][4] =   {   '1', '2', '3', 'A', 
                        '4', '5', '6', 'B', 
                        '7', '8', '9', 'C', 
                        '*', '0', '#', 'D'
                    };

// ISR
void kbi_irq_callback(uint gpio, uint32_t events) {
    EV_KBI = 1;
}

void set_rows_as_output(){
    // Rows init
    gpio_set_dir(ROW1, GPIO_OUT);
    gpio_set_dir(ROW2, GPIO_OUT);
    gpio_set_dir(ROW3, GPIO_OUT);
    gpio_set_dir(ROW4, GPIO_OUT);

    // Col init
    gpio_set_dir(COL1, GPIO_IN);
    gpio_set_dir(COL2, GPIO_IN);
    gpio_set_dir(COL3, GPIO_IN);
    gpio_set_dir(COL4, GPIO_IN);

    // Pull ups
    gpio_pull_up(COL1);
    gpio_pull_up(COL2);
    gpio_pull_up(COL3);
    gpio_pull_up(COL4);

    // Configure GPIO Interrupts
    gpio_set_irq_enabled_with_callback(COL1, GPIO_IRQ_EDGE_FALL, true, &kbi_irq_callback);
    gpio_set_irq_enabled(COL2, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(COL3, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(COL4, GPIO_IRQ_EDGE_FALL, true);
}

void set_rows_as_input(){
    // Configure GPIO Interrupts
    gpio_set_irq_enabled(COL1, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(COL2, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(COL3, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(COL4, GPIO_IRQ_EDGE_FALL, false);

    // Rows init
    gpio_set_dir(ROW1, GPIO_IN);
    gpio_set_dir(ROW2, GPIO_IN);
    gpio_set_dir(ROW3, GPIO_IN);
    gpio_set_dir(ROW4, GPIO_IN);

    // Col init
    gpio_set_dir(COL1, GPIO_OUT);
    gpio_set_dir(COL2, GPIO_OUT);
    gpio_set_dir(COL3, GPIO_OUT);
    gpio_set_dir(COL4, GPIO_OUT);

    // Enable pull ups
    gpio_pull_up(ROW1);
    gpio_pull_up(ROW2);
    gpio_pull_up(ROW3);
    gpio_pull_up(ROW4);
}

void kbi_init(){
    // Init rows and columns
    gpio_init(ROW1);
    gpio_init(ROW2);
    gpio_init(ROW3);
    gpio_init(ROW4);
    gpio_init(COL1);
    gpio_init(COL2);
    gpio_init(COL3);
    gpio_init(COL4);
    set_rows_as_output();
}

char get_key(){
    uint8_t col;
    uint8_t row;
    char key;

    if (!gpio_get(COL1)) col = 0;
    else if (!gpio_get(COL2)) col = 1;
    else if (!gpio_get(COL3)) col = 2;
    else if (!gpio_get(COL4)) col = 3;
    else col = 4;
    
    set_rows_as_input();

    if (!gpio_get(ROW1)) row = 0;
    else if (!gpio_get(ROW2)) row = 1;
    else if (!gpio_get(ROW3)) row = 2;
    else if (!gpio_get(ROW4)) row = 3;
    else row = 4;

    if (row == 4 || col == 4) {
        set_rows_as_output();
        return 'N';
    }

    key = keys[row][col];
    set_rows_as_output();

    return key;
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "kbi.h"

volatile bool key_pressed = false;

void kbi_irq_callback(uint gpio, uint32_t events) {
    key_pressed = true;
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
}

void set_rows_as_input(){
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

    // Pull ups
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

    // IRQ enable
    gpio_set_irq_enabled_with_callback(COL1, GPIO_IRQ_EDGE_FALL, true, &kbi_irq_callback);
    gpio_set_irq_enabled_with_callback(COL2, GPIO_IRQ_EDGE_FALL, true, &kbi_irq_callback);
    gpio_set_irq_enabled_with_callback(COL3, GPIO_IRQ_EDGE_FALL, true, &kbi_irq_callback);
    gpio_set_irq_enabled_with_callback(COL4, GPIO_IRQ_EDGE_FALL, true, &kbi_irq_callback);
}

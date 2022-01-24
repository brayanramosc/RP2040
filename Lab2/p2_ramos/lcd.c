#include <stdio.h>
#include "string.h"
#include "pico/stdlib.h"

#include "lcd.h"
#include "events.h"

void ports_init(void) {
    // Initialize ports
    gpio_init(RS);
    gpio_init(RW);
    gpio_init(E);
    gpio_init(D4);
    gpio_init(D5);
    gpio_init(D6);
    gpio_init(D7);

    // Set ports as output
    gpio_set_dir(RS, GPIO_OUT);
    gpio_set_dir(RW, GPIO_OUT);
    gpio_set_dir(E, GPIO_OUT);
    gpio_set_dir(D4, GPIO_OUT);
    gpio_set_dir(D5, GPIO_OUT);
    gpio_set_dir(D6, GPIO_OUT);
    gpio_set_dir(D7, GPIO_OUT);
}

void lcd_init(void) {
    ports_init();
}

void lcd_command(uint8_t cmd) {
    
}

void clear_screen() {
    gpio_put(RS, false);
    gpio_put(RW, false);


    gpio_put(E, true);
}
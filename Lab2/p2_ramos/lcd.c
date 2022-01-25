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

/*void lcd_command(uint8_t cmd) {
    
    gpio_put(RS, false);
    gpio_put(RW, false);
    gpio_put(E, true);
    gpio_put(E, false);
}*/

void lcd_char(uint8_t c) {
    gpio_put(RS, LCD_RS_DATA);
    gpio_put(RW, LCD_RW_WRITE);
    gpio_put(E, LCD_ENABLE);
    gpio_put(E, LCD_DISABLE);
}

// Check if LCD is ready to receive information
bool lcd_busy() {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_READ);

    return gpio_get(D7);
}

void clear_screen() {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    gpio_put(E, LCD_DISABLE);
}
/***************************************************************************
   ALAMBRADA (JM60)   
   
              PTC6 PTC4                          PTA0 PTA1 PTA2 PTA3 VCC
    _|____|____|____|____|____|____|____|____|____|____|____|____|____|__
   |           RS   E                             D4   D5   D6   D7   BL |
   | 1                                                                16 |
   |         LCD                                                         |
   |_____________________________________________________________________|
   
****************************************************************************/

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
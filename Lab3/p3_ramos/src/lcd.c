#include "string.h"
#include "pico/stdlib.h"

#include "lcd.h"

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

// Check if LCD is ready to receive information
bool lcd_busy(void) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_READ);
    gpio_set_dir(D7, GPIO_IN);
    bool busy = gpio_get(D7);
    gpio_set_dir(D7, GPIO_OUT);

    return busy;
}

// Pulse enable required to send data/command
void lcd_enable_pulse(void) {
    gpio_put(E, LCD_ENABLE);
    sleep_us(1);
    gpio_put(E, LCD_DISABLE);
}

// Send data/command in 4-bit mode
void lcd_send_4bit(uint8_t byte) {
    // Send MSB to LCD
    gpio_put(D4, (byte & 0x10) >> 4);
    gpio_put(D5, (byte & 0x20) >> 5);
    gpio_put(D6, (byte & 0x40) >> 6);
    gpio_put(D7, (byte & 0x80) >> 7);
    lcd_enable_pulse();
    
    // Send LSB to LCD
    gpio_put(D4, (byte & 0x01) >> 0);
    gpio_put(D5, (byte & 0x02) >> 1);
    gpio_put(D6, (byte & 0x04) >> 2);
    gpio_put(D7, (byte & 0x08) >> 3);
    lcd_enable_pulse();
}

// Send initial command
void lcd_init_cmd(uint8_t init_cmd) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(init_cmd);
}

void lcd_set_function (uint8_t bit_mode, uint8_t lines, uint8_t dots) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_SET_FUNCTION | bit_mode | lines | dots);
    sleep_us(42);
}

void lcd_onoff_control(uint8_t onoff_disp, uint8_t onoff_cursor, uint8_t onoff_blink) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_ONOFF_CONTROL | onoff_disp | onoff_cursor | onoff_blink);
    sleep_us(42);
}

void lcd_clear_screen(void) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_CLEAR);
    sleep_us(1640);
}

void lcd_entry_mode(uint8_t cursor_move, uint8_t display_move) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_ENTRY_MODE | cursor_move | display_move);
    sleep_us(42);
}

void lcd_cursor_at_home(void) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_CURSOR_HOME);
    sleep_us(1640);
}

void lcd_set_address_ddram (uint8_t address) {
    gpio_put(RS, LCD_RS_CMD);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(LCD_SET_DDRAM_ADDR | address);
    sleep_us(42);
}

// Initialize the LCD
void lcd_init(void) {
    ports_init();
    sleep_us(15000);
    lcd_init_cmd(LCD_INITIALIZE_CMD);

    sleep_us(4100);
    lcd_init_cmd(LCD_INITIALIZE_CMD);

    sleep_us(100);
    lcd_init_cmd(LCD_INITIALIZE_CMD);

    sleep_us(100);

    // Select lines and dots per character
    lcd_set_function(LCD_SET_FUNCTION_4BITS, LCD_SET_FUNCTION_2LINE, LCD_SET_FUNCTION_5x10);
    // Turn on the display and turn off the cursor and blinking
    lcd_onoff_control(LCD_ONOFF_CONTROL_DISP_ON, LCD_ONOFF_CONTROL_CURSOR_OFF, LCD_ONOFF_CONTROL_BLINK_OFF);
    // LCD clear
    lcd_clear_screen();
    // Set entry mode
    lcd_entry_mode(LCD_ENTRY_MODE_CURSOR_INC, LCD_ENTRY_MODE_DIPSNOSHIFT);
}

void lcd_send_char(uint8_t character) {
    gpio_put(RS, LCD_RS_DATA);
    gpio_put(RW, LCD_RW_WRITE);
    lcd_send_4bit(character);
    sleep_us(46);
}

void lcd_write_msg(uint8_t *msg, uint8_t address) {
    lcd_set_address_ddram(address);

    while (*msg != '\0') {
        lcd_send_char(*(msg++));
    }
}

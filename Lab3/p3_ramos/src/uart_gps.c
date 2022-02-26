/*
    Driver to manage GPS module NeoM8 24LC64 with 
    UART protocol in Raspberry pi Pico → RP2040
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"
#include "lcd.h"
#include "i2c_eeprom.h"
#include "uart_gps.h"

uint8_t ch;
uint8_t gps_key[] = {'$', 'G', 'N', 'G', 'G', 'A'};
uint8_t ch_idx = 0;
uint8_t ch_counter = 0;
uint8_t comma_counter = 0;
bool negativeNumber = false;
bool decimal = false;
float fact = 1;
uint8_t time[9];
uint8_t modified_time;
uint8_t coord_buff[2];
uint8_t time_buff[3];

enum charStates{ST_START, ST_COMMA_COUNT, ST_GET_TIME, ST_GET_LAT, ST_GET_LONG};
enum charStates charState;

// RX interrupt handler
void uart_handler(void) {
    EV_UART = 1;
    ch = uart_getc(UART_ID);
}

void read_data_from_uart (void) {
    printf("Char: %c\n", ch);
    switch (charState) {
        case ST_START:
            if (ch == gps_key[ch_idx]) {
                ch_idx++;
                if (++ch_counter == 6) {
                    ch_idx = 0;
                    ch_counter = 0;
                    charState = ST_COMMA_COUNT;
                }
            }else {
                ch_idx = 0;
                ch_counter = 0;
            }
            break;

        case ST_COMMA_COUNT:
            if (ch == ',') comma_counter++;

            if (comma_counter == 1) charState = ST_GET_TIME;
            else if (comma_counter == 2) charState = ST_GET_LAT;
            else if (comma_counter == 4) charState = ST_GET_LONG;
            break;

        case ST_GET_TIME:
            if (ch == ',') {
                modified_time = (time[0] & 0x0F)*10 + (time[1] & 0x0F);
                modified_time = modified_time > 5 ? modified_time - UTC_OFFSET : 24 - (UTC_OFFSET - modified_time);
                if (modified_time < 10){
                    time_buff[0] = '0';
                    time_buff[1] = (char)(modified_time + 48);
                }else sprintf(time_buff, "%d", modified_time);
                if (ch_counter == 0) {
                    lcd_clear_screen();
                    lcd_write_msg(SYNC_MESSAGE, LCD_COL1_LINE1);
                }else if(isTimeVisible){
                    snprintf(time, 9, "%c%c:%c%c:%c%c", time_buff[0], time_buff[1], time[2], time[3], time[4], time[5]);
                    lcd_clear_screen();
                    lcd_write_msg(TIME_MESSAGE, LCD_COL1_LINE1);
                    lcd_write_msg(time, LCD_COL1_LINE1 + 7);
                }
                comma_counter++;
                charState = ST_GET_LAT;
                ch_counter = 0;
                ch_idx = 0;
            }
            else {
                ch_counter++;
                time[ch_idx] = ch;
                ch_idx++;
            }
            break;

        case ST_GET_LAT:
            coord_buff[0] = ch;
            if(!isTimeVisible && ch != ','){
                lcd_write_msg(LAT_MESSAGE, LCD_COL1_LINE1);
                lcd_write_msg(coord_buff, LCD_COL1_LINE1 + 4 + ch_counter);
            }

            if (ch == '-') negativeNumber = true; 
            else if (ch == '.') {
                ch_counter++;
                decimal = true;
            }
            else if (ch == ',') {
                printf("Lat: %f \n", lat.fp);

                comma_counter++;
                if (ch_counter == 0) {
                    lcd_clear_screen();
                    lcd_write_msg(SYNC_MESSAGE, LCD_COL1_LINE1);
                }

                if(lat.fp != 0){
                    if (negativeNumber){
                        lat.fp = -1*longt.fp;
                        negativeNumber = false;
                    }
                    //write_block_to_eeprom(lat.bytes);
                    printf("Lat: %f \n", lat.fp);
                }
                charState = ST_COMMA_COUNT;
                ch_counter = 0;
                decimal = false;
                lat.fp = 0;
                fact = 1;
            }else{
                ch_counter++;
                if(decimal) fact /= 10;
                lat.fp = decimal ? lat.fp + ((ch & 0x0F)*fact) : lat.fp*10 + (ch & 0x0F);
            }
            break;
            
        case ST_GET_LONG:
            printf("Longt step: %c\n", ch);
            coord_buff[0] = ch;
            if(!isTimeVisible && ch != ','){
                lcd_write_msg(LONG_MESSAGE, LCD_COL1_LINE2);
                lcd_write_msg(coord_buff, LCD_COL6_LINE2 + ch_counter);
            }
            if (ch == '-') negativeNumber = true; 
            else if (ch == '.') {
                ch_counter++;
                decimal = true;
                /*if(!isTimeVisible){
                    lcd_write_msg(coord_buff, LCD_COL6_LINE2 + ch_counter);
                }*/
            }
            else if (ch == ',') {
                printf("Long: %f \n", longt.fp);

                if (ch_counter == 0) {
                    lcd_clear_screen();
                    lcd_write_msg(SYNC_MESSAGE, LCD_COL1_LINE1);
                }

                if(longt.fp != 0){
                    if (negativeNumber){
                        longt.fp = -1*longt.fp;
                        negativeNumber = false;
                    }
                    printf("Long: %f \n", longt.fp);
                    //write_block_to_eeprom(longt.bytes);
                }

                comma_counter = 0;
                decimal = false;
                charState = ST_START;
                ch_counter = 0;
                longt.fp = 0;
                fact = 1;
            }else{
                ch_counter++;
                if(decimal) fact /= 10;
                longt.fp = decimal ? longt.fp + ((ch & 0x0F)*fact) : longt.fp*10 + (ch & 0x0F);
                printf("Long: %f \n", longt.fp);

                if(ch_counter == 1 && ch == '0') {
                    ch_counter = 0;
                    break;
                }

                /*if(!isTimeVisible){
                    if(ch_counter == 1 && ch == '0') {
                        ch_counter = 0;
                        break;
                    }
                    /*lcd_write_msg(LONG_MESSAGE, LCD_COL1_LINE2);
                    lcd_write_msg(coord_buff, LCD_COL6_LINE2 + ch_counter);
                    //printf("Long: %c \n", ch);
                }*/
            }
            break;
        
        default:
            break;
    }
}

void uart_gps_init (void) {
    // Initialise UART
    uart_init(UART_ID, BAUD_RATE);

    // Set GPIO 12 as TX and GPIO 13 as RX
    gpio_set_function(UART_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_RX, GPIO_FUNC_UART);

    // Set data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's
    uart_set_fifo_enabled(UART_ID, false);

    // Set up and enable the interrupt handlers
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, uart_handler);
    irq_set_enabled(UART_IRQ, true);

    // Enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);
}

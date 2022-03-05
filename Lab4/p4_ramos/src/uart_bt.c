/*
    
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"
#include "uart_bt.h"

uint8_t ch;
uint8_t gps_key[] = {'$', 'G', 'N', 'G', 'G', 'A'};
uint8_t ch_idx = 0;
uint8_t ch_counter = 0;

enum charStates{ST_START, ST_GET_TIME, ST_GET_LAT};
enum charStates charState;

// RX interrupt handler
void uart_handler(void) {
    EV_UART = 1;
    ch = uart_getc(UART_ID);
}

void read_data_from_uart (void) {
    switch (charState) {
        case ST_START:
            if (ch == gps_key[ch_idx]) {
                ch_idx++;
                if (++ch_counter == 6) {
                    ch_idx = 0;
                    ch_counter = 0;
                    charState = ST_GET_TIME;
                }
            }else {
                ch_idx = 0;
                ch_counter = 0;
            }
            break;

        case ST_GET_TIME:
            if (ch == ',' && comma_counter == 1) {
                if (ch_counter == 0) {
                    lcd_clear_screen();
                    lcd_write_msg(SYNC_MESSAGE, LCD_COL1_LINE1);
                }
            } else if(ch == ',' && comma_counter == 0) comma_counter++;
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
                lcd_write_msg(coord_buff, LCD_COL5_LINE1 + ch_counter);
            }
            else if (ch == ',') {
                comma_counter++;
                if (ch_counter == 0) {
                    lcd_clear_screen();
                    lcd_write_msg(SYNC_MESSAGE, LCD_COL1_LINE1);
                }
                charState = ST_START;
                ch_counter = 0;
                decimal = false;
                fact = 1;
            }else{
                ch_counter++;
                if(decimal) fact /= 10;
                lat.fp = decimal ? lat.fp + ((ch & 0x0F)*fact) : lat.fp*10 + (ch & 0x0F);
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

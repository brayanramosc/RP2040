/*
    Driver to manage GPS module NeoM8 24LC64 with 
    UART protocol in Raspberry pi Pico → RP2040
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"
#include "uart_gps.h"

static int chars_rxed = 0;


// RX interrupt handler
void uart_handler(void) {
    EV_UART = 1;
}

void read_data_from_uart (void) {
    uint8_t ch = uart_getc(UART_ID);

    printf("%d \n", ch);
    printf("%c \n", ch);
    /*while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?
        if (uart_is_writable(UART_ID)) {
            // Change it slightly first!
            ch++;
            uart_putc(UART_ID, ch);
        }
        chars_rxed++;
    }*/
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

    printf("Init Finish!\n");
}



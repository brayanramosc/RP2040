#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"
#include "uart_bt.h"

volatile uint8_t ch;
uint8_t hex[] = {'0', '0'};
uint8_t dataBuffer[2];
uint8_t ch_idx = 0;
bool isValidFrame = false;

enum charStates{ST_START, ST_GET_VALUE, ST_GET_CS};
enum charStates charState;

// RX interrupt handler
void uart_handler(void) {
    EV_UART_RX = true;
    ch = uart_getc(UART_ID);
}

void read_data_from_uart (void) {
    switch (charState) {
        case ST_START:
            if (ch == '$') charState = ST_GET_VALUE;
            break;

        case ST_GET_VALUE:
            hex[ch_idx] = ch;
            if (ch_idx == 1) {
                ch_idx = 0;

                dataBuffer[0] = (int)strtol(hex, NULL, 16);
                //printf("value: %d, %X \n", dataBuffer[0], dataBuffer[0]);
                charState = ST_GET_CS;
            } else ch_idx++;
            
            break;

        case ST_GET_CS:
            hex[ch_idx] = ch;
            if (ch_idx == 1) {
                ch_idx = 0;

                dataBuffer[1] = (int)strtol(hex, NULL, 16);
                //printf("Checksum: %d, %X \n", dataBuffer[1], dataBuffer[1]);
                isValidFrame = ((HEADER_BYTE + dataBuffer[0]) & 0xFF) == dataBuffer[1] ? true : false;
                //printf("Frame is: %d\n\n", isValidFrame);
                charState = ST_START;
            } else ch_idx++;

            break;
        
        default:
            break;
    }
}

void uart_setup (void) {
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

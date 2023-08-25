#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "events.h"
#include "uart_bt.h"

volatile uint8_t ch;
uint8_t hex[] = {'0', '0'};
uint8_t dataBuffer[4];
uint8_t ch_idx = 0;
uint8_t mode;
uint8_t id;
bool isValidFrame = false;

volatile _fifo_t tx_fifo;
enum charStates{ST_START, ST_GET_MODE, ST_GET_VALUE, ST_GET_CS};
enum charStates charState;

// RX interrupt handler
void uart_handler(void) {
    if (uart_is_readable(UART_ID)) {
        EV_UART_RX = true;
        ch = uart_getc(UART_ID);
    }

    if(uart_is_writable(UART_ID)) send_data();
}

void write_data(void) {
    uint8_t chIdx = 0;
    
	while (chIdx < 4) {
        printf("Value: %d\n", dataBuffer[chIdx]);
		while (is_fifo_full());
		put_in_fifo (dataBuffer[chIdx]);
		chIdx++;
	}
}

bool is_fifo_full(void) {
    return (tx_fifo.ptr_put + 1) == tx_fifo.ptr_get || (tx_fifo.ptr_put - tx_fifo.ptr_get) == (FIFO_SIZE - 1);
}

bool is_fifo_empty(void) {
    return tx_fifo.ptr_put == tx_fifo.ptr_get;
}

void read_data_from_uart (void) {
    switch (charState) {
        case ST_START:
            if (ch == '$') charState = ST_GET_MODE;
            break;

        case ST_GET_MODE:
            hex[ch_idx] = ch;
            if (ch_idx == 1) {
                ch_idx = 0;
                
                dataBuffer[0] = HEADER_BYTE;
                dataBuffer[1] = (int)strtol(hex, NULL, 16);
                mode = GET_MODE(dataBuffer[1]);
                id = GET_ID(dataBuffer[1]);

                printf("\n Mode: %d, %X \n", mode, mode);
                printf("ID: %d, %X \n", id, id);

                charState = ST_GET_VALUE;
            } else ch_idx++;
            
            break;

        case ST_GET_VALUE:
            hex[ch_idx] = ch;
            if (ch_idx == 1) {
                ch_idx = 0;

                dataBuffer[2] = (int)strtol(hex, NULL, 16);
                printf("value: %d, %X \n", dataBuffer[2], dataBuffer[2]);
                charState = ST_GET_CS;
            } else ch_idx++;
            
            break;

        case ST_GET_CS:
            hex[ch_idx] = ch;
            if (ch_idx == 1) {
                ch_idx = 0;

                dataBuffer[3] = (int)strtol(hex, NULL, 16);
                isValidFrame = ((HEADER_BYTE + dataBuffer[1] + dataBuffer[2]) & 0xFF) == dataBuffer[3] ? true : false;
                
                printf("Checksum: %d, %X \n", dataBuffer[3], dataBuffer[3]);
                printf("Frame is: %d\n\n", isValidFrame);
                charState = ST_START;
            } else ch_idx++;

            break;
        
        default:
            break;
    }
}

void put_in_fifo (uint8_t val) {
    tx_fifo.buff[tx_fifo.ptr_put] = val;
    if (tx_fifo.ptr_put == (FIFO_SIZE - 1)) tx_fifo.ptr_put = 0;
    else tx_fifo.ptr_put++; 
    uart_set_irq_enables(UART_ID, true, true);
}

void send_data (void) {
    uint8_t val;

    if (!is_fifo_empty()) {
        val = tx_fifo.buff[tx_fifo.ptr_get];
        if (tx_fifo.ptr_get == (FIFO_SIZE - 1)) tx_fifo.ptr_get = 0;
        else tx_fifo.ptr_get++; 
        printf("Value to send: %d\n", val);
        uart_putc(UART_ID, (char)val);
    } else uart_set_irq_enables(UART_ID, true, false);
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

    // Initialise SW FIFO
    tx_fifo.ptr_put = 0;
    tx_fifo.ptr_get = 0;
}

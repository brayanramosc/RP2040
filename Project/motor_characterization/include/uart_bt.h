#ifndef _UART_BT_H_
#define _UART_BT_H_

// UART values
#define UART_ID             uart0
#define BAUD_RATE           9600
#define DATA_BITS           8
#define STOP_BITS           1
#define PARITY              UART_PARITY_NONE
#define UART_TX             12
#define UART_RX             13

// Commands values
#define HEADER_BYTE         0x24

// Extern variables
extern uint8_t dataBuffer[2];
extern uint8_t value;
extern uint8_t checksum;
extern bool isValidFrame;

// Functions
void uart_setup (void);
void read_data_from_uart (void);

#endif

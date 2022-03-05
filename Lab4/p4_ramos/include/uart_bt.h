#ifndef _UART_BT_H_
#define _UART_BT_H_

// Help values
#define UART_ID             uart0
#define BAUD_RATE           9600
#define DATA_BITS           8
#define STOP_BITS           1
#define PARITY              UART_PARITY_NONE
#define UART_TX             12
#define UART_RX             13

// Functions
void uart_gps_init (void);
void read_data_from_uart (void);

#endif

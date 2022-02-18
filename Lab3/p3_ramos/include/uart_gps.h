#ifndef _UART_GPS_H_
#define _UART_GPS_H_

// Help values
#define UART_ID             uart0
#define BAUD_RATE           9600
#define DATA_BITS           8
#define STOP_BITS           1
#define PARITY              UART_PARITY_NONE
#define UART_TX             12
#define UART_RX             13
#define WRITE               0x00
#define READ                0x01 

// Functions
void uart_gps_init (void);
void read_data_from_uart (void);

#endif

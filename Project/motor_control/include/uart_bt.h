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
#define MONITOR_BYTE        0x40
#define CONTROL_BYTE        0x80
#define OPEN_LOOP_BYTE      0x20
#define CLOSED_LOOP_BYTE    0x21

// FIFO values
#define FIFO_SIZE           5

typedef struct {
    volatile uint8_t buff[FIFO_SIZE];
    volatile uint8_t ptr_put;
    volatile uint8_t ptr_get;
} _fifo_t;

extern volatile _fifo_t tx_fifo;

// Help values
#define GET_MODE(X)         ((X) & 0xC0)
#define GET_ID(X)           ((X) & 0x3F)

// Extern variables
extern bool isWaitingForByte;
extern uint8_t dataBuffer[4];
extern uint8_t mode;
extern uint8_t id;
extern uint8_t value;
extern uint8_t checksum;
extern bool isValidFrame;

// Functions
void uart_setup (void);
bool is_fifo_full(void);
bool is_fifo_empty(void);
void put_in_fifo (uint8_t);
void read_data_from_uart (void);
void send_data (void);

#endif

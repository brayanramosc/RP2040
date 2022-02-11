#ifndef _UART_GPS_H_
#define _UART_GPS_H_

// Help values
#define UART_ID             uart0
#define BAUD_RATE           115200
#define DATA_BITS           8
#define STOP_BITS           1
#define PARITY              UART_PARITY_NONE
#define UART_TX             12
#define UART_RX             13
#define WRITE               0x00
#define READ                0x01   

#define EEPROM_ID           0xA0
#define EEPROM_ID_7BITS     (EEPROM_ID >> 1)
#define NUM_PAGES           256
#define BYTES_PER_PAGE      32

#define FIRST_ADDR          0x0000
#define MSB_ADRESS(hex)     ((hex) >> 8)
#define LSB_ADRESS(hex)     (((hex) >> 0) & 0xFF)

// Functions
void uart_gps_init (void);

#endif

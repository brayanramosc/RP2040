#ifndef _I2C_EEPROM_H_
#define _I2C_EEPROM_H_

// Help values
#define I2C_ID              i2c0
#define SDA_PIN             16
#define SCL_PIN             17
#define BAUDRATE            100000
#define WRITE               0x00
#define READ                0x01   

#define EEPROM_ID           0xA0
#define EEPROM_ID_7BITS     (EEPROM_ID >> 1)
#define NUM_PAGES           256
#define BYTES_PER_PAGE      32

#define FIRST_ADDR          0x0000
#define MSB_ADRESS(hex)     ((hex) >> 8)
#define LSB_ADRESS(hex)     (((hex) >> 0) & 0xFF)

extern uint8_t data_buff[4];

// Functions
void i2c_eeprom_init (void);
void erase_data (void);
void write_block_to_eeprom (uint8_t*);
void read_from_eeprom (void);

#endif

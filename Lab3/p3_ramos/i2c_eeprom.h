#ifndef _I2C_EEPROM_H_
#define _I2C_EEPROM_H_

// Help values
#define SDA_PIN         16
#define SCL_PIN         17
#define BAUDRATE        100000
#define EEPROM_ID       0xA0
#define WRITE           0x00
#define READ            0x01   

// Functions
void i2c_eeprom_init(void);

#endif

/*
    Driver to manage EEPROM 24LC64 with I2C protocol in Raspberry pi Pico → RP2040
    This EEPROM has 256 pages of 32 bytes each one
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c_eeprom.h"

uint16_t w_address = FIRST_ADDR;
uint16_t r_address = FIRST_ADDR;
uint8_t page_counter = 0;
uint8_t data_buff[4];

// Initialize the i2c protocol
void i2c_eeprom_init (void) {
    i2c_init(I2C_ID, BAUDRATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

// Reset addresses
void erase_data (void) {
    w_address = FIRST_ADDR;
    r_address = FIRST_ADDR; 
    page_counter = 0;
}

void write_block_to_eeprom (uint8_t* block) {
    uint8_t address[2];
    address[0] = MSB_ADRESS(w_address);
    address[1] = LSB_ADRESS(w_address);

    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, address, sizeof(address), true) == PICO_ERROR_GENERIC);
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, block, sizeof(block), false) == PICO_ERROR_GENERIC);

    printf("%X\n", EEPROM_ID_7BITS);
    w_address += (uint16_t)sizeof(block);
    page_counter += (w_address % 32 == 0) ? 1 : 0;
    printf("Writed: %c %c %c %c\n", block[0], block[1], block[2], block[3]);
    printf("Current Address: %X\n", w_address);
}

void read_from_eeprom (void) {
    uint8_t address[2];
    address[0] = MSB_ADRESS(r_address);
    address[1] = LSB_ADRESS(r_address);

    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, address, sizeof(address), true) == PICO_ERROR_GENERIC);
    while(i2c_read_blocking(I2C_ID, EEPROM_ID_7BITS, data_buff, sizeof(data_buff), false) == PICO_ERROR_GENERIC);

    r_address += (uint16_t)sizeof(data_buff);
    printf("Read: %c %c %c %c\n", data_buff[0], data_buff[1], data_buff[2], data_buff[3]);
    printf("Current r Address: %X\n", r_address);
}

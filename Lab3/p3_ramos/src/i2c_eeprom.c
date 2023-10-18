/*
    Driver to manage EEPROM 24LC64 with I2C protocol in Raspberry pi Pico → RP2040
    This EEPROM has 256 pages of 32 bytes each one
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "events.h"
#include "i2c_eeprom.h"

uint16_t w_address = FIRST_ADDR;
uint16_t r_address = FIRST_ADDR;
uint8_t page_counter = 0;
uint8_t data_buff[4];

// Initialise addresses and write them in EEPROM
void init_adresses (void) {
    uint8_t address[2] = {0x00, 0x00};

    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, address, sizeof(address), true) == PICO_ERROR_GENERIC);
    while(i2c_read_blocking(I2C_ID, EEPROM_ID_7BITS, data_buff, sizeof(data_buff), false) == PICO_ERROR_GENERIC);

    uint16_t temp_key;
    uint8_t temp_val[4];
    temp_key = (data_buff[0] << 8) | (data_buff[1]);

    if (temp_key == KEY_VALUE ) {
        r_address = W_ADDR;
        read_from_eeprom();

        w_address = (data_buff[0] << 8) | (data_buff[1]);
        r_address = (data_buff[2] << 8) | (data_buff[3]);
    } else {
        temp_val[0] = MSB_ADRESS(KEY_VALUE);
        temp_val[1] = LSB_ADRESS(KEY_VALUE);
        temp_val[2] = 0x00;
        temp_val[3] = 0x00;

        write_block_to_eeprom(temp_val);
        w_address = FIRST_DATA_ADDR;
        r_address = FIRST_DATA_ADDR;
    } 
    #if RUN_MODE == DEBUG
        printf("Current w_Address 1: %X\n", w_address);
        printf("Current r_Address 1: %X\n\n", r_address);
    #endif
}

// Initialise the i2c protocol
void i2c_eeprom_init (void) {
    i2c_init(I2C_ID, BAUDRATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    init_adresses();
}

// Reset addresses
void erase_data (void) {
    uint8_t reset_data[4];

    reset_data[0] = MSB_ADRESS(W_ADDR);
    reset_data[1] = LSB_ADRESS(W_ADDR);
    reset_data[2] = MSB_ADRESS(FIRST_DATA_ADDR);
    reset_data[3] = LSB_ADRESS(FIRST_DATA_ADDR);
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, reset_data, sizeof(reset_data), false) == PICO_ERROR_GENERIC);
    
    reset_data[0] = MSB_ADRESS(R_ADDR);
    reset_data[1] = LSB_ADRESS(R_ADDR);
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, reset_data, sizeof(reset_data), false) == PICO_ERROR_GENERIC);

    w_address = FIRST_DATA_ADDR;
    r_address = FIRST_DATA_ADDR;
    page_counter = 0;
}

void write_block_to_eeprom (uint8_t* bytes) {
    uint8_t block[6];
    uint8_t updated_addr[4];

    block[0] = MSB_ADRESS(w_address);
    block[1] = LSB_ADRESS(w_address);

    for (int i = 0; i < sizeof(bytes); i++) {
        block[i + 2] = bytes[i];
    }
    
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, block, sizeof(block), false) == PICO_ERROR_GENERIC);

    w_address += ((uint16_t)sizeof(block) - 2);
    page_counter += (w_address % 32 == 0) ? 1 : 0;

    updated_addr[0] = MSB_ADRESS(W_ADDR);
    updated_addr[1] = LSB_ADRESS(W_ADDR);
    updated_addr[2] = MSB_ADRESS(w_address);
    updated_addr[3] = LSB_ADRESS(w_address);
    
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, updated_addr, 4, false) == PICO_ERROR_GENERIC);
}

void read_from_eeprom (void) {
    uint8_t address[2];
    uint8_t updated_addr[4];
    
    address[0] = MSB_ADRESS(r_address);
    address[1] = LSB_ADRESS(r_address);

    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, address, sizeof(address), true) == PICO_ERROR_GENERIC);
    while(i2c_read_blocking(I2C_ID, EEPROM_ID_7BITS, data_buff, sizeof(data_buff), false) == PICO_ERROR_GENERIC);
    
    r_address += (uint16_t)sizeof(data_buff);

    updated_addr[0] = MSB_ADRESS(R_ADDR);
    updated_addr[1] = LSB_ADRESS(R_ADDR);
    updated_addr[2] = MSB_ADRESS(r_address);
    updated_addr[3] = LSB_ADRESS(r_address);
    
    while(i2c_write_blocking(I2C_ID, EEPROM_ID_7BITS, updated_addr, 4, false) == PICO_ERROR_GENERIC);
}

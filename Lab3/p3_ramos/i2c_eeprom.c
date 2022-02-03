#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c_eeprom.h"

void i2c_eeprom_init(void) {
    i2c_init(i2c0, BAUDRATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void write_byte_to_eeprom(uint8_t addr, uint8_t byte) {
    i2c_write_blocking(i2c0, addr, &byte, 1, false);
}

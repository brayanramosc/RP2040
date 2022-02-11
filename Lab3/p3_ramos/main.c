#include "pico/stdlib.h"
#include "events.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "i2c_eeprom.h"

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    kbi_init();
    lcd_init();
    i2c_eeprom_init();

    // Check for timer
    while (!timer_init(MAIN_PERIOD));

    // Infinite loop
    while (true){
        events_controller();
    }

    return 0;
}

#include "pico/stdlib.h"
#include "events.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "uart_gps.h"

#define MAIN_PERIOD 5

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    kbi_init();
    lcd_init();
    uart_gps_init();

    // Check for timer
    while (!timer_init(MAIN_PERIOD));

    // Infinite loop
    while (true){
        events_controller();
    }

    return 0;
}

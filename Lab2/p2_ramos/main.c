#include "pico/stdlib.h"
#include "events.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    kbi_init();
    rtc_setup();
    lcd_init();

    // Check for timer
    while (!timer_init(MAIN_PERIOD));

    // Infinite loop
    events_controller();

    return 0;
}

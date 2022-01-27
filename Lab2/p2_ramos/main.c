#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"

#define MAIN_PERIOD 5

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    kbi_init();
    rtc_setup();
    lcd_init();

    // Check for timer
    while (!timer_init(MAIN_PERIOD));

    // Infinite loop
    while (true){
        events_controller();
    }

    return 0;
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"

#define MAIN_PERIOD 5 
//#define DEBOUNCE_MS 10
//#define LED_PIN 15

int main(){
    // Initialization
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    kbi_init();
    rtc_setup();
    lcd_init();

    // Check for timer
    while (!timer_init(MAIN_PERIOD));

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif
    printf("Looooooop\n");

    // Infinite loop
    while (true){
        events_controller();
    }

    return 0;
}

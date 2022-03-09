#include "pico/stdlib.h"
#include "events.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif
    adc_setup();
    pwm_setup();

    // Check for timer
    while (!timer_init(TIMER_PERIOD_MS));

    // Infinite loop
    events_controller();

    return 0;
}

#include "pico/stdlib.h"
#include "events.h"
#include "timer.h"
#include "pwm.h"
#include "uart_bt.h"
#include "adc.h"

int main(){
    // Initialization
    stdio_init_all();

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif
    pwm_setup();
    adc_setup();
    uart_setup();

    // Check for timer
    while (!timer_init(TIMER_PERIOD_MS));

    // Infinite loop
    events_controller();

    return 0;
}

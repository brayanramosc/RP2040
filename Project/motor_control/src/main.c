#include "pico/stdlib.h"
#include "events.h"
#include "timer.h"
#include "pwm.h"
#include "uart_bt.h"
#include "tasks.h"

static void hardwareInit (void) {
    // Initialization
    stdio_init_all();
    pwm_setup();
    uart_setup();

    // Check for timer
    while (!timer_init(TIMER_PERIOD_MS));
    
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
}

int main(){
    hardwareInit();
    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    createTasks();
    
    // Infinite loop
    //events_controller();

    return 0;
}

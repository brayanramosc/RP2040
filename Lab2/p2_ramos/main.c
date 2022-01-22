#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"

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

    while (!timer_init(MAIN_PERIOD));

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected());
    #endif

    // Infinite loop
    while (true){
        events_controller();
        /*if (timer_request)
        {
            timer_request = false;
            if (key_pressed) {
                if (++counter == DEBOUNCE_MS)
                {
                    key = get_key();
                    key_pressed = false;
                    counter = 0;
                    #if RUN_MODE == DEBUG
                        if (key != 'N')
                        {
                            printf("Tecla: %c\n", key);
                            print_current_time();
                        }
                        
                    #endif
                }
            }
        }*/
    }

    return 0;
}

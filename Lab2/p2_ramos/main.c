#include <stdio.h>
#include "pico/stdlib.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"

#define RUN_MODE DEBUG
#define MAIN_PERIOD 1 
#define DEBOUNCE_MS 50 
#define LED_PIN 15

int main(){
    // Initialization
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    kbi_init();
    rtc_setup();

    while (!timer_init(MAIN_PERIOD)){
        tight_loop_contents();
    }
    
    char key;
    uint8_t counter = 0;
    uint32_t completeMenu;

    // Check for USB connection
    #if RUN_MODE == DEBUG
        while (!stdio_usb_connected()) {
            printf(".");
            sleep_ms(500);
        }
    #endif

    // Infinite loop
    while (true){
        if (timer_request)
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
        }
    }

    return 0;
}

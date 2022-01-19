#include <stdio.h>
#include "pico/stdlib.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"

#define RUN_MODE DEBUG
#define LED_PIN 15

int main(){
    // Initialization
    stdio_init_all();
    kbi_init();
    rtc_setup();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    char key;
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
        #if RUN_MODE == DEBUG
            //print_current_time();
            if (key_pressed) {
                alarm_init(DEBOUNCE_MS);
                key_pressed = false;
                //printf("Evento de tecla\n");
            }
            if (timer_fired)
            {
                key = get_key();
                //printf("Antirrebote\n");
                printf("Letra: %c\n", key);
                timer_fired = false;
                key_pressed = false;
                print_current_time();
            }
            
        #else
            /****************************** Timer Request ******************************/
            if(temperature_timer_request)
            {
                temperature_timer_request = false;
                adc_capture(ADC_NUM_TEMP);
            } 

            if(light_timer_request)
            {
                light_timer_request = false;
                adc_capture(ADC_NUM_LIGHT);
            }
        #endif
    }

    return 0;
}

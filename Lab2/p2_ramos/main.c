#include <stdio.h>
#include "pico/stdlib.h"

#include "rtc.h"

#define LED_PIN 2

int main(){
    // Initialization
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    bool menuFlag = true;
    uint32_t completeMenu;

    // Check for USB connection
    while (!stdio_usb_connected()) {
        printf(".");
        sleep_ms(500);
    }

    // Infinite loop
    while (true){
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
    }

    return 0;
}

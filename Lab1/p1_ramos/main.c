#include <stdio.h>
#include "pico/stdlib.h"

#include "serialUtils.h"
#include "timer.h"
#include "adc.h"

#define MIN_TEMPERATURE_THRESHOLD 10
#define MAX_TEMPERATURE_THRESHOLD 50
#define FAN_PIN 2

int main(){
    // Initialization
    stdio_init_all();
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);
    gpio_put(FAN_PIN, true);

    timer_init(TEMP_TIMER_PERIOD, LIGHT_TIMER_PERIOD);
    adc_setup();

    bool menuFlag = true;
    uint32_t option;
    uint32_t tempThreshold = MAX_TEMPERATURE_THRESHOLD;

    // Check for USB connection
    while (!stdio_usb_connected()) {
        printf(".");
        sleep_ms(500);
    }

    printf(MENU_MESSAGE);

    // Infinite loop
    while (true){
        if(temperature_timer_request)
        {
            temperature_timer_request = false;
            printf("Interrupcion temp dada: %ld\n", time_us_32());
            adc_capture_temperature();
        }

        if(light_timer_request)
        {
            light_timer_request = false;
            printf("Interrupcion luz dada: %ld\n", time_us_32());
            adc_capture_light_perc();
        }

        if(temperature_adc_request)
        {
            temperature_adc_request = false;
            printf("Conversion temp dada: \n");
        }

        if(light_adc_request)
        {
            light_adc_request = false;
            printf("Conversion light dada: \n");
        }

        if (menuFlag)
        {
            option = GetOption();
            if (option != PICO_ERROR_TIMEOUT)
            {
                menuFlag = false;
            }
        }
        else
        {
            switch (option)
            {
                case 1:
                    printf("Valores: \n");
                    printf("Temperatura: %d °C\t", tempThreshold);
                    printf("Porcentaje de luz: %d%%\n", tempThreshold);
                    printf(MENU_MESSAGE);
                    menuFlag = true;
                    break;
                case 2:
                    printf("Opcion 2 :3 \n");
                    tempThreshold = GetThreshold(MIN_TEMPERATURE_THRESHOLD, MAX_TEMPERATURE_THRESHOLD);
                    if (tempThreshold != PICO_ERROR_TIMEOUT){
                        printf("Actualizacion completa!\n\n");
                    }
                    menuFlag = true;
                    break;
                
                default:
                    break;
            }
        }
    }

    return 0;
}

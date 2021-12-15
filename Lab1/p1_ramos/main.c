#include <stdio.h>
#include "pico/stdlib.h"

#include "serialUtils.h"
#include "timer.h"
#include "adc.h"

#define MIN_TEMPERATURE_THRESHOLD 10
#define MAX_TEMPERATURE_THRESHOLD 130
#define MIN_LIGHT_PERCENTAGE_THRESHOLD 20
#define MAX_LIGHT_PERCENTAGE_THRESHOLD 100
#define FAN_PIN 2
#define LED_PIN 15

int main(){
    // Initialization
    stdio_init_all();
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);
    gpio_put(FAN_PIN, true);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    timer_init(TEMP_TIMER_PERIOD, LIGHT_TIMER_PERIOD);
    adc_setup();

    bool menuFlag = true;
    uint32_t option;
    float tempThreshold = MAX_TEMPERATURE_THRESHOLD;
    float tempRead = tempThreshold;
    float lightPercThreshold = MIN_LIGHT_PERCENTAGE_THRESHOLD;
    float lightPercRead = lightPercThreshold;

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
            /*printf("Interrupcion temp dada: %ld\n", time_us_32());
            tempRead = adc_capture_temperature();*/
        }

        if(light_timer_request)
        {
            light_timer_request = false;
            printf("Interrupcion luz dada: %ld\n", time_us_32());
            lightPercRead = adc_capture_light_perc();
        }

        if(temperature_adc_request)
        {
            temperature_adc_request = false;
            printf("Conversion temp dada: %.2f\n", tempRead);
            if (tempRead > tempThreshold)
            {
                gpio_put(FAN_PIN, false);
            }
            else
            {
                gpio_put(FAN_PIN, true);
            }
            
        }

        if(light_adc_request)
        {
            light_adc_request = false;
            printf("Conversion light dada: %.2f\n", lightPercRead);
            if (lightPercRead < lightPercThreshold)
            {
                gpio_put(LED_PIN, true);
            }
            else
            {
                gpio_put(LED_PIN, false);
            }
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
                    printf("Temperatura: %f °C\t", tempThreshold);
                    printf("Porcentaje de luz: %f%%\n", tempThreshold);
                    printf(MENU_MESSAGE);
                    menuFlag = true;
                    break;
                case 2:
                    printf("Opcion 2... \n");
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

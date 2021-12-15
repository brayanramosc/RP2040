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
    uint32_t completeMenu;

    float tempThreshold = MAX_TEMPERATURE_THRESHOLD;
    uint32_t auxTemp = 0;
    float tempRead = tempThreshold;

    float lightPercThreshold = MIN_LIGHT_PERCENTAGE_THRESHOLD;
    uint32_t auxLightPerc = 0;
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
            //printf("Interrupcion luz dada: %ld\n", time_us_32());
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
            //printf("Conversion light dada: %.2f\n", lightPercRead);
            if (lightPercRead < lightPercThreshold)
            {
                gpio_put(LED_PIN, true);
            }
            else
            {
                gpio_put(LED_PIN, false);
            }
        }

        completeMenu = TestFunction(&auxTemp, 
                     &auxLightPerc, 
                     tempRead, 
                     lightPercRead,
                     MIN_TEMPERATURE_THRESHOLD,
                     MAX_TEMPERATURE_THRESHOLD,
                     MIN_LIGHT_PERCENTAGE_THRESHOLD,
                     MAX_LIGHT_PERCENTAGE_THRESHOLD);

        if (completeMenu != PICO_ERROR_TIMEOUT)
        {
            if (auxTemp != 0 && auxLightPerc != 0)
            {
                printf("Tempaux: %d \t Lightaux: %d \n\n", auxTemp, auxLightPerc);

                lightPercThreshold = (float)auxLightPerc;
                tempThreshold = (float)auxTemp;

                printf("Temp: %.2f \t Light: %.2f \n\n", tempThreshold, lightPercThreshold);
            }
        }
        

        /*if (menuFlag)
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
                    printf("Temperatura: %.2f grados Celsius\t", tempRead);
                    printf("Porcentaje de luz: %.2f%%\n\n", lightPercRead);
                    printf(MENU_MESSAGE);
                    menuFlag = true;
                    break;
                case 2:
                    auxLightPerc = GetThreshold(MIN_LIGHT_PERCENTAGE_THRESHOLD, MAX_LIGHT_PERCENTAGE_THRESHOLD);

                    if (auxLightPerc != PICO_ERROR_TIMEOUT){
                        lightPercThreshold = (float)auxLightPerc;
                        auxTemp = GetThreshold(MIN_TEMPERATURE_THRESHOLD, MAX_TEMPERATURE_THRESHOLD);

                        if (auxTemp != PICO_ERROR_TIMEOUT){
                            printf("Actualizacion completa!\n\n");
                            tempThreshold = auxTemp;

                            menuFlag = true;
                            printf(MENU_MESSAGE);
                        }
                    }
                    break;
                
                default:
                    break;
            }
        }*/
    }

    return 0;
}

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
    float voltage_mv;
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
        /****************************** Timer Request ******************************/
        if(temperature_timer_request)
        {
            temperature_timer_request = false;
            //printf("Interrupcion temp dada: %ld\n", time_us_32());
            //tempRead = adc_capture_temperature();
            adc_capture(ADC_NUM_TEMP);
        }

        if(light_timer_request)
        {
            light_timer_request = false;
            //printf("Interrupcion luz dada: %ld\n", time_us_32());
            //lightPercRead = adc_capture_light_perc();
            adc_capture(ADC_NUM_LIGHT);
        }

        /******************************* ADC Request ******************************/
        if(temperature_adc_request)
        {
            temperature_adc_request = false;
            voltage_mv = (raw_value * ADC_CONVERSION_FACTOR) * 1000;
            tempRead = voltage_mv / 10;     // 1°C per 10mV

            //printf("voltage: %.2f V \t mV: %.2f \t temp: %.2f\n", raw_value * ADC_CONVERSION_FACTOR, voltage_mv, tempRead);
            
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
            lightPercRead = (raw_value * 100) / ADC_RANGE;
            
            //printf("voltage: %.2f V \t \t light: %.2f\n", raw_value * ADC_CONVERSION_FACTOR, lightPercRead);

            if (lightPercRead < lightPercThreshold)
            {
                gpio_put(LED_PIN, true);
            }
            else
            {
                gpio_put(LED_PIN, false);
            }
        }

        /********************************* Menu *********************************/
        completeMenu = GetMenuOption(&auxTemp, 
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
                lightPercThreshold = (float)auxLightPerc;
                tempThreshold = (float)auxTemp;
            }
        }
    }

    return 0;
}

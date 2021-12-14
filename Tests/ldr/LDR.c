#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)
#define ADC_VREF 3.3f
#define ADC_RANGE (1 << 12)
#define ADC_CONVERSION_FACTOR (ADC_VREF / ADC_RANGE)

//const uint LED_PIN = 14;    // GPIO14

int main(){
    // Initialization
    stdio_init_all();
    //gpio_init(LED_PIN);
    //gpio_set_dir(LED_PIN, GPIO_OUT);

    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);
    adc_irq_set_enabled(true);

    // Infinite loop
    while (true){
        uint16_t raw_value = adc_read();
        float voltage = raw_value * ADC_CONVERSION_FACTOR;
        float light_percentage = (raw_value/ADC_RANGE)*100;
        
        printf("Raw value: %d, voltage: %.2f V\n", raw_value, voltage);
        printf("Porcentaje de luz: %.2f%%\n", light_percentage);
        int level = adc_fifo_get_level();
        printf("level: %d \n", level);
        sleep_ms(1000);
    }
    
    return 0;
}

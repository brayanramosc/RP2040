#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

#include "adc.h"
#include "events.h"

volatile uint16_t adc_raw_value;

// ISR
void adc_handler () {
    if (!adc_get_selected_input()) EV_ADC_LIGHT = true;
    else EV_ADC_TEMP = true;
    
    adc_raw_value = adc_fifo_get();
    adc_raw_value = adc_fifo_get();
    adc_run(false);
}

// ADC Setup
void adc_setup() {
    adc_init();
    adc_gpio_init(ADC_PIN_LIGHT);
    adc_gpio_init(ADC_PIN_TEMP);

    adc_fifo_setup(
        true,
        false,
        2,
        false,
        false
    );
    
    adc_irq_set_enabled(true);
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_handler);
    irq_set_enabled(ADC_IRQ_FIFO, true);
}

// Capturing data
void adc_capture(uint8_t adc_num) {
    adc_fifo_drain();
    adc_select_input(adc_num);
    adc_run(true);
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

#include "adc.h"
#include "events.h"

volatile uint16_t adc_raw_value;

// ISR
void adc_handler () {
    EV_ADC = true;
    
    adc_raw_value = adc_fifo_get();
    adc_raw_value = adc_fifo_get();
    adc_run(false);
}

// ADC Setup
void adc_setup() {
    adc_init();
    adc_gpio_init(ADC_PIN);

    adc_fifo_setup(true, false, 2, false, false);
    
    adc_irq_set_enabled(true);
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_handler);
    irq_set_enabled(ADC_IRQ_FIFO, true);
}

// Capturing data
void adc_capture() {
    adc_fifo_drain();
    adc_select_input(ADC_NUM);
    adc_run(true);
}

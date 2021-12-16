#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

#include "adc.h"

volatile bool temperature_adc_request = false;
volatile bool light_adc_request = false;
volatile uint16_t raw_value;

// ISR
void adc_handler ()
{
    if (!adc_get_selected_input())
    {
        light_adc_request = true;
    }
    else
    {
        temperature_adc_request = true;
    }
    
    raw_value = adc_fifo_get();
    adc_run(false);
}

// ADC Setup
void adc_setup()
{
    adc_gpio_init(ADC_PIN_TEMP);
    adc_gpio_init(ADC_PIN_LIGHT);
    adc_init();

    adc_fifo_setup(
        true,
        false,
        1,
        false,
        false);

}

// Capturing data
void adc_capture(uint8_t adc_num)
{
    adc_fifo_drain();
    adc_select_input(adc_num);
    adc_run(true);
    
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_handler);
    adc_irq_set_enabled(true);
    irq_set_enabled(ADC_IRQ_FIFO, true);
}

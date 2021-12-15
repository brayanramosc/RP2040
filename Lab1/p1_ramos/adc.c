#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

#include "adc.h"

volatile bool temperature_adc_request = false;
volatile bool light_adc_request = false;

void temperature_adc_handler(){
    printf("ADC Temp Interrupt!!\n\n");
    temperature_adc_request = true;
    adc_run(false);
    adc_fifo_drain();
}

void light_adc_handler(){
    //printf("ADC Light Interrupt!!\n\n");
    light_adc_request = true;
    adc_run(false);
    adc_fifo_drain();
}

void adc_setup(){
    adc_gpio_init(ADC_PIN_TEMP);
    adc_gpio_init(ADC_PIN_LIGHT);
    adc_init();
    // adc_set_round_robin(0x03);      // Sample GPIO 26 and 27

    adc_fifo_setup(
        true,
        false,
        2,
        false,
        false
    );

}

float adc_capture_temperature(){
    uint8_t level;
    uint16_t raw_value;
    float voltage;
    float voltage_mv;
    float temperature;
    adc_fifo_drain();
    
    adc_select_input(ADC_NUM_TEMP);
    adc_run(true);

    irq_set_exclusive_handler (ADC_IRQ_FIFO, temperature_adc_handler);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);

	printf("Empezando conversion... \n");

    raw_value = adc_fifo_get();
	level = adc_fifo_get_level();
    printf("Obteniendo valor de la FIFO... \n");
    voltage = raw_value * ADC_CONVERSION_FACTOR;
    voltage_mv = voltage * 1000;        // (voltage-DIODE_OFFSET_VOLTAGE)*1000 millivolts
    temperature = voltage_mv / 10;      // 1°C per 10mV 

    printf("adc: input: %u \t empty: %d \t level: %u \t input: %u\n\n",
			adc_get_selected_input(),
			adc_fifo_is_empty(),
			level,
			adc_get_selected_input());
    
    printf("Raw value: %d \t voltage: %.2f V \t mV: %.2f\n", raw_value, voltage, voltage_mv);
    printf("Temperatura: %.2f Celsius\n\n", temperature);

    return temperature;
}

float adc_capture_light_perc(){
    uint8_t level;
    uint16_t raw_value;
    float voltage;
    float light_percentage;
    adc_fifo_drain();

    //printf("Inicializando... \n");
    
    adc_select_input(ADC_NUM_LIGHT);
    adc_run(true);

    //printf("Inicializado... \n");

    irq_set_exclusive_handler (ADC_IRQ_FIFO, light_adc_handler);
	adc_irq_set_enabled(true);
    irq_set_enabled(ADC_IRQ_FIFO, true);

    //printf("Empezando conversion... \n");

    raw_value = adc_fifo_get();
	level = adc_fifo_get_level();
    //printf("Obteniendo valor de la FIFO... \n");
    voltage = raw_value * ADC_CONVERSION_FACTOR;
    light_percentage = (raw_value*100)/ADC_RANGE;

    //printf("adc: input: %u \t empty: %d \t level: %u \t input: %u\n\n",
	//		adc_get_selected_input(),
	//		adc_fifo_is_empty(),
	//		level,
	//		adc_get_selected_input());
    
    //printf("Raw value: %d \t voltage: %.2f V\n", raw_value, voltage);
    //printf("Porcentaje de luz: %.2f%%\n\n", light_percentage);

    return light_percentage;
}
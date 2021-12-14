#ifndef _ADC_H
#define _ADC_H

#define ADC_NUM_TEMP 0
#define ADC_PIN_TEMP (26 + ADC_NUM_TEMP)
#define ADC_NUM_LIGHT 1
#define ADC_PIN_LIGHT (26 + ADC_NUM_LIGHT)
#define ADC_VREF 3.3f
#define ADC_RANGE (1 << 12)
#define ADC_CONVERSION_FACTOR (ADC_VREF / ADC_RANGE)
#define DIODE_OFFSET_VOLTAGE 0.929

extern volatile bool temperature_adc_request;
extern volatile bool light_adc_request;

void adc_setup(void);
void adc_capture_temperature(void);
void adc_capture_light_perc(void);

#endif
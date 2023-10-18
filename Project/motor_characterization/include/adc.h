#ifndef _ADC_H
#define _ADC_H

#define ADC_NUM                 0
#define ADC_PIN                 (26 + ADC_NUM)
#define ADC_VREF                3.3f
#define ADC_RANGE               (1 << 12)
#define ADC_CONVERSION_FACTOR   (ADC_VREF / ADC_RANGE)
#define ADC_CONVERSION(X)       ((float)(X) * ADC_CONVERSION_FACTOR)

extern volatile uint16_t adc_raw_value;

void adc_setup(void);
void adc_capture(void);

#endif

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "pwm.h"
#include "uart_bt.h"
#include "adc.h"

volatile _events_str _events;

uint16_t counter = 0;
uint16_t counter2 = 0;
bool isValueRead = false;
float voltage = 0;
float period = 0;
float freq = 0;
float rpm = 0;
bool isFirstStepComplete = false;
bool isSecondStepComplete = false;
bool isCount = false;
uint16_t idx = 0;
uint16_t i1 = 0;
float data[1000];

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;
			
			if (isCount) counter++;
			

			/*if (levelValue == 12500) { // 1875 -> 15%
				if (counter2 == 0) {
					printf("Empezando captura... \n");
				}
				
				if (++counter2 <= ONE_SECONDS_CNT*2) {
					adc_capture();
				}
			}
			
			if (isValueRead) {
				isValueRead = false;
            	voltage = ADC_CONVERSION(adc_raw_value);
				printf("%f,", voltage);
			}*/

			/*if (++counter == ONE_SECONDS_CNT) {
				counter = 0;
				freq = measure_frequency(PWM_GPIO_MEASURE);
				//printf("Frecuencia medida: %f Hz\n\n", freq);
			}*/

			if (isSecondStepComplete) {
				printf("Obteniendo valores!\n");
				isSecondStepComplete = false;
				
				for (uint16_t i = 0; i < 1000; i++) {
					printf("%f,", data[i]);
				}
			}
		}

		if (EV_EDGE) {
			EV_EDGE = false;

			if ((t2-t1) > 500) {
				period = ((float)(t2-t1)) / 1000000;
				freq = 1 / period;
				rpm = (freq * 60) / 20;

				if (levelValue == 2000) { 
					isCount = true;
					if (counter <= ONE_SECONDS_CNT*2 && rpm > 0) {
						data[idx] = rpm;
						idx++;
					} else {
						counter = 0;
						pwm_change_level(12500);
						isFirstStepComplete = true;
						isCount = false;
						i1 = idx;
					}
				}
				else if (levelValue == 12500 && isFirstStepComplete) { 
					if (idx < 1000 && rpm > 0) {
						data[idx] = rpm;
						idx++;
					} else { 
						idx = 0;
						isSecondStepComplete = true;
						isFirstStepComplete = false;
						printf("Segunda fase completada!\n");
					}
				}
			}
		}
		
		if (EV_ADC) {
			EV_ADC = false;
			//isValueRead = true;
		}

		if (EV_UART_RX) {
			EV_UART_RX = false;
			read_data_from_uart();

			if(isValidFrame) {
				isValidFrame = false;
				pwm_change_level((uint16_t)((uint32_t)(dataBuffer[0]*PWM_TOP/100)));
			}
		}
	}
}

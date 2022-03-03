#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "general.h"
#include "timer.h"
#include "adc.h"

uint8_t lightReadCnt 	= 0;
uint8_t tempReadCnt  	= 0;
bool 	isLightRead	 	= false;
bool 	isTempRead 	 	= false;
float 	voltage_mv 	 	= 0;
float 	lightPercRead 	= 0;
float 	tempRead 		= 0;
bool	readDataFromUART = false;

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;

			if (isLightRead) {
				isLightRead = false;
            	lightPercRead = (raw_value * 100) / ADC_RANGE;
				printf("Valor crudo para la luz: %d\n", raw_value);
				printf("Porcentaje de luz leido: %f\n", lightPercRead);
			}
			if (isTempRead) {
				isTempRead = false;
            	temperature_adc_request = false;
				voltage_mv = ADC_CONVERSION(raw_value) * 1000;
				tempRead = voltage_mv / 10;    // 1°C per 10mV
				printf("Valor crudo para la temp: %d\n", raw_value);
				printf("Valor en mV para la temp: %f\n", voltage_mv);
				printf("Temp leida: \n\n", tempRead);
			}

			if(++lightReadCnt == HALF_SECOND_CNT){
				lightReadCnt = 0;
				adc_capture(ADC_NUM_LIGHT);
			}
			if(++tempReadCnt == ONE_SECONDS_CNT){
				tempReadCnt = 0;
				adc_capture(ADC_NUM_TEMP);
			}
		}
		if (EV_ADC_LIGHT) {
			EV_ADC_LIGHT = false;
			isLightRead = true;
		}
		if (EV_ADC_TEMP) {
			EV_ADC_TEMP = false;
			isTempRead = true;
		}
		if (EV_UART) {
			EV_UART = false;

			if(readDataFromUART){
				read_data_from_uart();
			}
		}
	}
}

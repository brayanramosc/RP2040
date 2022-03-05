#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "general.h"
#include "timer.h"
#include "adc.h"

volatile _events_str _events;

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
            	lightPercRead = (adc_raw_value * 100) / ADC_RANGE;
				printf("Porcentaje de luz leido: %f\n", lightPercRead);
			}
			if (isTempRead) {
				isTempRead = false;
				voltage_mv = ADC_CONVERSION(adc_raw_value) * 1000;
				tempRead = voltage_mv / 10;    // 1°C per 10mV
				printf("Temp leida: %f\n\n", tempRead/2);
			}

			if(++lightReadCnt == HALF_SECOND_CNT){
				lightReadCnt = 0;
				adc_capture(ADC_NUM_LIGHT);
			} else if(++tempReadCnt == ONE_SECONDS_CNT){
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
		/*if (EV_UART) {
			EV_UART = false;

			if(readDataFromUART){
				read_data_from_uart();
			}
		}*/
	}
}

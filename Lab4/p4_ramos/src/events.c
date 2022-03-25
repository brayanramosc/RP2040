#include <stdio.h>
#include "pico/stdlib.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include "uart_bt.h"

volatile _events_str _events;

uint8_t lightReadCnt 	= 0;
uint8_t tempReadCnt  	= 0;
uint8_t waitForByteCnt	= 0;
bool 	isLightRead	 	= false;
bool 	isTempRead 	 	= false;
float 	voltage_mv 	 	= 0;
uint8_t	lightPercRead 	= 0;
uint8_t	tempRead 		= 0;
bool	readDataFromUART = false;
uint8_t chIdx			= 0;

void write_data(void) {
	while (chIdx < 4) {
		while (is_fifo_full());
		put_in_fifo (dataBuffer[chIdx]);
		chIdx++;
	}
	chIdx = 0;
}

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;

			if (isWaitingForByte) waitForByteCnt++;

			if (isLightRead) {
				isLightRead = false;
            	lightPercRead = (uint8_t)((adc_raw_value * 100) / ADC_RANGE);
				//printf("Porcentaje de luz leido: %d\n\n", lightPercRead);
			}
			if (isTempRead) {
				isTempRead = false;
				voltage_mv = ADC_CONVERSION(adc_raw_value) * 1000;
				tempRead = (uint8_t)(voltage_mv / 10 / 2);    // 1°C per 10mV
				//printf("Temp leida: %d\n\n", tempRead);
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

		if (EV_UART_RX) {
			EV_UART_RX = false;
			read_data_from_uart();

			if(isValidFrame && mode == CONTROL_BYTE ) {
				isValidFrame = false;
				if (id == LED_BYTE) {
					pwm_change_level(PWM_LED_CH, (uint16_t)((uint32_t)(dataBuffer[2]*PWM_TOP/100)));
				} else if (id == MOTOR_BYTE) {
					pwm_change_level(PWM_MOTOR_CH, (uint16_t)((uint32_t)(dataBuffer[2]*PWM_TOP/100)));
				}
				write_data();
			} else if(isValidFrame && mode == MONITOR_BYTE ) {
				isValidFrame = false;
				if (id == LIGHT_BYTE) dataBuffer[2] = lightPercRead;
				else if (id == TEMPERATURE_BYTE) dataBuffer[2] = tempRead;
				dataBuffer[3] = (HEADER_BYTE + dataBuffer[1] + dataBuffer[2]) & 0xFF;
				write_data();
			}
		}
	}
}

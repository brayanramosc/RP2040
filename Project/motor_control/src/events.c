#include <stdio.h>
#include "pico/stdlib.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "pwm.h"
#include "uart_bt.h"

volatile _events_str _events;

uint8_t waitForByteCnt	= 0;
bool	readDataFromUART = false;
uint8_t chIdx			= 0;

void write_data(void) {
	uint8_t chIdx = 0;
	
	while (chIdx < 4) {
		while (is_fifo_full());
		put_in_fifo (dataBuffer[chIdx]);
		chIdx++;
	}
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
		}

		/*if (EV_UART_RX) {
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
		}*/
	}
}

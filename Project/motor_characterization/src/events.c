#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "pwm.h"
#include "uart_bt.h"

volatile _events_str _events;

uint8_t counter = 0;
float freq = 0;
float duty = 0;

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;

			if (++counter == ONE_SECONDS_CNT) {
				counter = 0;
				freq = measure_frequency(PWM_GPIO_MEASURE);
				printf("Frecuencia medida: %f Hz\n\n", freq);
			}
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

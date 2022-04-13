#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "pwm.h"

volatile _events_str _events;

uint8_t counter = 0;
float freq = 0;

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;

			if (++counter == 2) {
				counter = 0;
				freq = measure_frequency(PWM_GPIO_MEASURE);

				printf("Frecuencia real: %d KHz\n", clock_get_hz(clk_sys) / PWM_LEVEL_VALUE /1000);
				printf("Frecuencia medida: %f KHz\n\n", freq);
			}
			
		}
	}
}

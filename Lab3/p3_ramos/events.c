#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "events.h"
#include "general.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "uart_gps.h"

volatile _events_str _events;
uint8_t 	debounce_counter 	= 0;
bool 		isCounting 	= false;
bool 		isDataOnUART = false;
char 		key[2];
uint8_t 	state 	= 0;

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;

			if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				isCounting = false;
				key[0] = get_key();

				/*if (key[0] != 'N') {
					config_handler(&state, key);
				}*/
				if (key[0] == 'D') {
					read_data_from_uart();
				}
			}
		}

		if (EV_KBI) {
			EV_KBI = 0;

			debounce_counter = 0;
			isCounting = true;
		}

		if (EV_UART) {
			EV_UART = 0;

			printf("Evento en UART!");

			isDataOnUART = true;
		}
	}
}

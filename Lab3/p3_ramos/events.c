#include "pico/stdlib.h"
#include "string.h"
#include "events.h"
#include "general.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "utils.h"

volatile _events_str _events;
uint8_t 	debounce_counter 	= 0;
bool 		isCounting 	= false;
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

				if (key[0] != 'N') {
					else config_handler(&state, key);
				}
			}
		}

		if (EV_KBI) {
			EV_KBI = 0;

			debounce_counter = 0;
			isCounting = true;
		}
	}
}

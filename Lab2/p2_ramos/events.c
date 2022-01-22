#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "general.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"

volatile _events_str _events;
volatile uint8_t 	debounce_counter = 0;
//volatile bool 		isCounting 	= false;
char key;

// Events controller
void events_controller(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;

			//if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				//isCounting = false;
				/*key = get_key();
				printf("Tecla: %c\n", key);*/

				if (EV_KBI) {
					if (++debounce_counter == DEBOUNCE_MS) {
						key = get_key();
						EV_KBI = 0;
						debounce_counter = 0;

						if (key != 'N'){
							#if RUN_MODE == DEBUG
								printf("Tecla: %c\n", key);
								print_current_time();
							#endif
						}
					}
				}
			//}
		}

		/*if (EV_KBI) {
			EV_KBI = 0;
			printf("KBI! \n");

			debounce_counter = DEBOUNCE_MS;
			isCounting = true;
		}*/
	}
}

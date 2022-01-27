#include <stdio.h>
#include "pico/stdlib.h"
#include "events.h"
#include "general.h"
#include "rtc.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"

volatile _events_str _events;
uint8_t 	debounce_counter = 0;
bool 		isCounting 	= false;
char 		key;

// Events controller
void events_controller(void) {
	lcd_write_msg(CONGIF_MESSAGE, LCD_COL1_LINE2);
	
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;

			if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				isCounting = false;
				key = get_key();

				if (key != 'N') {
					#if RUN_MODE == DEBUG
						printf("Tecla: %c\n", key);
					#endif
					#if RUN_MODE == DEBUG
						if (key == 'A') {
							printf("Tecla: %c\n", key);
							print_date_and_time();
							printf("\n");
						}
						
					#endif
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

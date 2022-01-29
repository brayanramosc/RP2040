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
uint8_t 	print_time_counter 	= 0;
uint16_t 	led_on_counter 		= 0;
bool 		isLedCounter		= false;
bool 		isCounting 	= false;
char 		key[2];
uint8_t 	state 	= 0;

// Events controller
void events_controller(void) {
	gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;
			
			if (++print_time_counter == PRINT_TIME_COUNT && state == 0) {
				lcd_write_msg(get_date_and_time_str(), LCD_COL1_LINE1);
				lcd_write_msg(CONFIG_MESSAGE, LCD_COL1_LINE2);
				print_time_counter = 0;
			}

			if (isLedCounter && ++led_on_counter == LED_ON_COUNT) {
				isLedCounter = false;
				gpio_put(LED_PIN, false);
			}

			if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				isCounting = false;
				key[0] = get_key();

				if (key[0] != 'N') {
					if (isLedCounter && key[0] == 'B') {
						gpio_put(LED_PIN, false);
					} else config_handler(&state, key);
				}
			}
		}

		if (EV_KBI) {
			EV_KBI = 0;

			debounce_counter = 0;
			isCounting = true;
		}

		if (EV_RTC) {
			EV_RTC = 0;
			gpio_put(LED_PIN, true);

			led_on_counter = 0;
			isLedCounter = true;
		}
	}
}

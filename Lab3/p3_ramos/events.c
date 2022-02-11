#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "events.h"
#include "general.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "i2c_eeprom.h"
//#include "utils.h"

volatile _events_str _events;
uint8_t 	debounce_counter = 0;
bool 		isCounting = false;
char 		key[2];
uint8_t 	state 	= 0;

// Events controller
void events_controller(void) {
	ieee754 data;
	data.fp = 2.531545;
	erase_data();
	lcd_write_msg(OPT1_MESSAGE, LCD_COL1_LINE1);
	lcd_write_msg(OPT2_MESSAGE, LCD_COL1_LINE2);

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
					//else config_handler(&state, key);
					if (key[0] == 'A') {
						printf("Sent: %c %c %c %c\n", data.chr[0], data.chr[1], data.chr[2], data.chr[3]);
						write_block_to_eeprom(data.chr);
						/*write_block_to_eeprom(&data.chr[1]);
						write_block_to_eeprom(&data.chr[2]);
						write_block_to_eeprom(&data.chr[3]);*/
						data.fp = 1.1416;
						printf("Fp: %f \n", data.fp);
					}
					if (key[0] == 'B') {
						read_from_eeprom();
						
						data.chr[0] = data_buff[0];
						data.chr[1] = data_buff[1];
						data.chr[2] = data_buff[2];
						data.chr[3] = data_buff[3];
						printf("Chars: %c %c %c %c\n", data.chr[0], data.chr[1], data.chr[2], data.chr[3]);
						printf("FP: %f\n", data.fp);
					}
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

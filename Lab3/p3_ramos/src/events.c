#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "events.h"
#include "general.h"
#include "kbi.h"
#include "timer.h"
#include "lcd.h"
#include "i2c_eeprom.h"
#include "uart_gps.h"

volatile _events_str _events;

ieee754    	lat, longt;
uint8_t 	debounce_counter = 0;
bool 		isCounting = false;
char 		key[2];
uint8_t 	state 	= 0;
bool 		isDataOnUART = false;

// Events controller
void events_controller(void) {
	lat.fp = 2.531545;
	//erase_data();
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

				/*if (key[0] != 'N') {
					config_handler(&state, key);
				}*/
				if (key[0] == 'D') {
					read_data_from_uart();
				}
				if (key[0] != 'N') {
					//else config_handler(&state, key);
					if (key[0] == 'A') {
						write_block_to_eeprom(lat.bytes);
					}else if (key[0] == 'B') {
						read_from_eeprom();
						
						lat.bytes[0] = data_buff[0];
						lat.bytes[1] = data_buff[1];
						lat.bytes[2] = data_buff[2];
						lat.bytes[3] = data_buff[3];
						printf("FP: %f\n", lat.fp);
					}else if (key[0] == 'C') {
						erase_data();
					}
				}
			}
		}

		if (EV_KBI) {
			EV_KBI = 0;

			debounce_counter = 0;
			isCounting = true;
		}

		/*if (EV_UART) {
			EV_UART = 0;

			printf("Evento en UART!");

			isDataOnUART = true;
		}*/
	}
}

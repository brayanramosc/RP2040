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
bool 		isTimeVisible = true;
uint8_t 	debounce_counter  = 0;
uint16_t 	show_data_counter = 0;
bool 		isCounting = false;
char 		key[2];
uint8_t 	state 	= 0;
bool 		readDataFromUART = false;

// Events controller
void events_controller(void) {
	//lat.fp = 2.531545;
	//erase_data();
	lcd_write_msg(OPT1_MESSAGE, LCD_COL1_LINE1);
	lcd_write_msg(OPT2_MESSAGE, LCD_COL1_LINE2);

	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;

			if(++show_data_counter == SHOW_DATA_CNT){
				isTimeVisible = !isTimeVisible;
				show_data_counter = 0;
			}

			if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				isCounting = false;
				key[0] = get_key();

				if (key[0] == '1') {
					readDataFromUART = true;
				} else if (key[0] == '2' && !readDataFromUART) {
					printf("KML!! \n");
					read_from_eeprom();

					for (int i = 0; i < 4; i++) {
						lat.bytes[i] = data_buff[i];
						longt.bytes[i + 4] = data_buff[i + 4];
					}
					printf("FP lat: %f\n", lat.fp);
					printf("FP longt: %f\n", longt.fp);
				}
				
				if (key[0] == 'D') {
					read_data_from_uart();
				}
				if (key[0] != 'N') {
					//else config_handler(&state, key);
					if (key[0] == 'A') {
						printf("FP lat: %f\n", lat.fp);
						printf("FP longt: %f\n", longt.fp);
						write_block_to_eeprom(lat.bytes);
						write_block_to_eeprom(longt.bytes);
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

		if (EV_UART) {
			EV_UART = 0;

			if(readDataFromUART){
				read_data_from_uart();
			}
		}
	}
}

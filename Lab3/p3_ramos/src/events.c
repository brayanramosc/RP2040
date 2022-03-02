#include <stdio.h>
#include <math.h>
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
uint16_t 	no_usb_counter	  = 0;
bool 		isCounting = false;
bool 		noUSBdetect = false;
char 		key[2];
uint8_t 	state 	= 0;
bool 		readDataFromUART = false;
bool     	saveCoords;

void get_coords_from_eeprom(void) {
	read_from_eeprom();
	for (int i = 0; i < 4; i++) {
		lat.bytes[i] = data_buff[i];
		//longt.bytes[i + 4] = data_buff[i + 4];
	}
	read_from_eeprom();
	for (int i = 0; i < 4; i++) {
		longt.bytes[i] = data_buff[i];
	}
	coords_to_degrees();
}

// Convert gps format (DDMM.MMMM, DDDMM.MMMMM) to degrees
void coords_to_degrees(void) {
	int lat_degrees = (int)(lat.fp / 100);
	int longt_degrees = (int)(longt.fp / 100);
	float lat_mm_mmm = fmod(lat.fp, 100);
	float longt_mm_mmm = fmod(longt.fp, 100);

	lat.fp = lat_degrees + (lat_mm_mmm / 60);
	longt.fp = longt_degrees + (longt_mm_mmm / 60);
}

// Events controller
void events_controller(void) {
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

			if(noUSBdetect && ++no_usb_counter < TWO_SECONDS_CNT) {
				lcd_clear_screen();
				lcd_write_msg(NO_USB_MESSAGE1, LCD_COL1_LINE1);
				lcd_write_msg(NO_USB_MESSAGE2, LCD_COL1_LINE2);
			}else{noUSBdetect = false;}
			
			if(!readDataFromUART && !noUSBdetect){
				lcd_clear_screen();
				lcd_write_msg(OPT1_MESSAGE, LCD_COL1_LINE1);
				lcd_write_msg(OPT2_MESSAGE, LCD_COL1_LINE2);
			}

			if (isCounting && ++debounce_counter == DEBOUNCE_MS) {
				isCounting = false;
				key[0] = get_key();

				if (key[0] == '1') {
					readDataFromUART = true;
				} else if (key[0] == '2' && !readDataFromUART) {
					if (stdio_usb_connected()) {
						printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
						printf("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
						printf("  <Document>\n");
						printf("    <Style id=\"customStyle\">\n");
						printf("      <LineStyle>\n");
						printf("        <color>ff0000ff</color>\n");
						printf("        <width>10</width>\n");
						printf("      </LineStyle>\n");
						printf("    </Style>\n");
						printf("    <Placemark>\n");
						printf("      <name>Super Ruta</name>\n");
						get_coords_from_eeprom();
						printf("      <LookAt>\n");
						printf("        <longitude>%f</longitude>\n", longt.fp);
						printf("        <latitude>%f</latitude>\n", lat.fp);
						printf("        <range>1450</range>\n");
						printf("      </LookAt>\n");
						r_address -= 8;
						printf("      <styleUrl>#customStyle</styleUrl>\n");
						printf("      <LineString>\n");
						printf("        <coordinates>\n");
						
						while (w_address != r_address) {
							get_coords_from_eeprom();
							printf("          %f,%f\n", longt.fp, lat.fp);  
						}
						
						printf("        </coordinates>\n");
						printf("      </LineString>\n");
						printf("    </Placemark>\n");
						printf("  </Document>\n");
						printf("</kml>\n");
						erase_data();
					} else {
						noUSBdetect = true;
						no_usb_counter = 0;
					}

				} else if (key[0] == 'A'  && readDataFromUART) {
					saveCoords = true;
				} else if (key[0] == 'C') {
					erase_data();
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

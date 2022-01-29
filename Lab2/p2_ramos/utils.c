#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "utils.h"
#include "rtc.h"
#include "lcd.h"

uint16_t 	year	= 0;
uint8_t 	month	= 0;
uint8_t 	day		= 0;
uint8_t 	hour	= 0;
uint8_t 	minute	= 0;
uint8_t     mode    = 0;

void print_two_lines(bool clear, uint8_t *msg1, uint8_t *msg2, uint8_t dir_msg1, uint8_t dir_msg2) {
    if (clear) {
        lcd_clear_screen();
    }
    
    lcd_write_msg(msg1, LCD_COL1_LINE1);
    lcd_write_msg(msg2, dir_msg2);
}

uint8_t digits_counter(uint16_t number) {
	uint8_t count = 0;

	do {
		number /= 10;
		++count;
	} while (number != 0);
	
	return count;
}

void config_handler(uint8_t *state, char *key) {
    if (key[0] == 'A' && *state == 0) {
        print_two_lines(true, OPT1_MESSAGE, OPT2_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);

        *state = 1;
    } else if (key[0] == '1' && *state == 1) {
        print_two_lines(true, SAVE_MESSAGE, YEAR_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
        mode = SET_TIME_MODE;

        *state = 2;
    } else if (key[0] == '2' && *state == 1) {
        print_two_lines(true, SAVE_MESSAGE, YEAR_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
        mode = SET_ALARM_MODE;

        *state = 2;
    } else if (*state == 2) {
        if (key[0] >= '0' && key[0] <= '9') {
            if (digits_counter(year) < 4) {
                year =  year*10 + (key[0] & 0x0F);
                if (year != 0) {
                    print_two_lines(false, SAVE_MESSAGE, key, LCD_COL1_LINE1, LCD_COL7_LINE2 + (digits_counter(year) - 1));
                }
            }
        }else if (key[0] == 'D' && digits_counter(year) == 4) {
            mode == SET_TIME_MODE ? set_year(year) : set_year_alarm(year);
            print_two_lines(true, SAVE_MESSAGE, MONTH_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
            year = 0;
            *state = 3;
        }
    } else if (*state == 3) {
        if (key[0] >= '0' && key[0] <= '9') {
            if (digits_counter(month) < 2) {
                month =  month*10 + (key[0] & 0x0F);
                if (month != 0) {
                    print_two_lines(false, SAVE_MESSAGE, key, LCD_COL1_LINE1, LCD_COL6_LINE2 + (digits_counter(month) - 1));
                }
            }
        }else if (key[0] == 'D' && (digits_counter(month) == 1 || digits_counter(month) == 2) && month != 0) {
            if(month <= 12) {
                mode == SET_TIME_MODE ? set_month(month) : set_month_alarm(month);
                print_two_lines(true, SAVE_MESSAGE, DAY_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
                *state = 4;
            } else {
                print_two_lines(true, SAVE_MESSAGE, MONTH_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
            }
            month = 0;
        }
    } else if (*state == 4) {
        if (key[0] >= '0' && key[0] <= '9') {
            if (digits_counter(day) < 2) {
                day =  day*10 + (key[0] & 0x0F);
                if (day != 0 && digits_counter(day) <= 2) {
                    print_two_lines(false, SAVE_MESSAGE, key, LCD_COL1_LINE1, LCD_COL6_LINE2 + (digits_counter(day) - 1));
                }
            }
        }else if (key[0] == 'D' && (digits_counter(day) == 1 || digits_counter(day) == 2) && day != 0) {
            if (day <= 31) {
                mode == SET_TIME_MODE ? set_day(day) : set_day_alarm(day);
                print_two_lines(true, SAVE_MESSAGE, HOUR_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
                *state = 5;
            }else {
                print_two_lines(true, SAVE_MESSAGE, DAY_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
            }
            day = 0;
        }
    } else if (*state == 5) {
        if (key[0] >= '0' && key[0] <= '9') {
            if (digits_counter(hour) < 2) {
                hour =  hour*10 + (key[0] & 0x0F);
                if (hour != 0 && digits_counter(hour) <= 2) {
                    print_two_lines(false, SAVE_MESSAGE, key, LCD_COL1_LINE1, LCD_COL7_LINE2 + (digits_counter(hour) - 1));
                }
            } 
        }else if (key[0] == 'D' && (digits_counter(hour) == 1 || digits_counter(hour) == 2) && hour != 0) {
            if (hour <= 24) {
                mode == SET_TIME_MODE ?  set_hour(hour) : set_hour_alarm(hour);
                print_two_lines(true, SAVE_MESSAGE, MINUTE_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
                *state = 6;
            }else {
                print_two_lines(true, SAVE_MESSAGE, HOUR_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
            }
            hour = 0;
        }
    } else if (*state == 6) {
        if (key[0] >= '0' && key[0] <= '9') {
            if (digits_counter(minute) < 2) {
                minute =  minute*10 + (key[0] & 0x0F);
                if (digits_counter(minute) <= 2) {
                    print_two_lines(false, SAVE_MESSAGE, key, LCD_COL1_LINE1, LCD_COL10_LINE2 + (digits_counter(minute) - 1));
                }
            } 
        }else if (key[0] == 'D' && (digits_counter(minute) == 1 || digits_counter(minute) == 2)) {
            if (minute <= 59) {
                mode == SET_TIME_MODE ?  set_minute(minute) : set_minute_alarm(minute);
                *state = 0;
            }else {
                print_two_lines(true, SAVE_MESSAGE, MINUTE_MESSAGE, LCD_COL1_LINE1, LCD_COL1_LINE2);
            }
            minute = 0;
        }
    }
}

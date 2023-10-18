#include <stdio.h>
#include <stdlib.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "rtc.h"
#include "events.h"

char datetime_buf[256];
char *datetime_str = &datetime_buf[0];
char lcd_datatime_format[17];

// Current time struct
datetime_t t = {
    .year   = 2022,
    .month  = 01,
    .day    = 25,
    .dotw   = 2,
    .hour   = 22,
    .min    = 40,
    .sec    = 00
};

// Alarm struct
datetime_t alarm = {
    .year   = 2022,
    .month  = 01,
    .day    = 25,
    .dotw   = 2,
    .hour   = 22,
    .min    = 40,
    .sec    = 00
};

// Callback
void rtc_callback(void){
    EV_RTC = 1;
}

void rtc_setup(void){
    rtc_init();
    rtc_set_datetime(&t);
}

void set_alarm(void) {
    rtc_set_alarm(&alarm, rtc_callback);
}

char* get_date_and_time_str(void) {
    rtc_get_datetime(&t);

    snprintf(lcd_datatime_format, 
            17, 
            "%02d/%02d/%d %02d:%02d", 
            t.day, t.month, t.year, t.hour, t.min);

    return lcd_datatime_format;
}

// Set current time
void set_year(uint16_t year) {
    t.year = year;
}

void set_month(uint8_t month) {
    t.month = month;
}

void set_day(uint8_t day) {
    t.day = day;
}

void set_hour(uint8_t hour) {
    t.hour = hour;
}

void set_minute(uint8_t min) {
    t.min = min;
    t.sec = 0;
    rtc_set_datetime(&t);
}

// Set alarm
void set_year_alarm(uint16_t year) {
    alarm.year = year;
}

void set_month_alarm(uint8_t month) {
    alarm.month = month;
}

void set_day_alarm(uint8_t day) {
    alarm.day = day;
}

void set_hour_alarm(uint8_t hour) {
    alarm.hour = hour;
}

void set_minute_alarm(uint8_t min) {
    alarm.min = min;
    alarm.sec = 0;
    set_alarm();
}

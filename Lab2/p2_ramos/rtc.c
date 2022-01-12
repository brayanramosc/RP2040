#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "rtc.h"

volatile bool alarm_fired = false;
char datetime_buf[256];
char *datetime_str = &datetime_buf[0];

datatime_t t = {
    .year   = 2022,
    .month  = 01,
    .day    = 07,
    .dotw   = 5,
    .hour   = 22,
    .min    = 40,
    .sec    = 00
};

// Callback
void rtc_callback(){
    alarm_fired = true;
}

void rtc_setup(){
    rtc_init();
    rtc_set_datetime(&t);
}

void print_current_time(){
    rtc_get_datetime(&t);
    datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
    printf("\r%s      ", datetime_str);
}

#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "rtc.h"

volatile bool alarm_fired = false;
char datetime_buf[256];
char *datetime_str = &datetime_buf[0];

datetime_t t = {
    .year   = 2022,
    .month  = 01,
    .day    = 25,
    .dotw   = 3,
    .hour   = 22,
    .min    = 40,
    .sec    = 00
};

// Callback
void rtc_callback(){
    alarm_fired = true;
}

void rtc_setup(void){
    rtc_init();
    rtc_set_datetime(&t);
}
 
void print_date_and_time(void) {
    rtc_get_datetime(&t);
    char datetime_buf[17];
    snprintf(datetime_buf, sizeof(datetime_buf), "%02d/%02d/%d %02d:%02d", t.day, t.month, t.year, t.hour, t.min);
    printf(datetime_buf);
}

void print_current_time(void){
    rtc_get_datetime(&t);
    datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
    printf("\r%s      \n", datetime_str);
}

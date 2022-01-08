#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "rtc.h"

volatile bool alarm_request = false;

// Callback
void rtc_callback(){
    alarm_request = true;
}

void rtc_setup(){
    rtc_init();
    rtc_set_datetime(&t);
}

#ifndef _RTC_H
#define _RTC_H

#define TEMP_TIMER_PERIOD 500 

datatime_t t = {
    .year   = 2022,
    .month  = 01,
    .day    = 07,
    .dotw   = 5,
    .hour   = 22,
    .min    = 40,
    .sec    = 00
};



//extern struct repeating_timer temp_timer;
//extern struct repeating_timer light_timer;
//extern volatile bool temperature_timer_request;
//extern volatile bool light_timer_request;

//bool timer_init(int32_t, int32_t);

#endif

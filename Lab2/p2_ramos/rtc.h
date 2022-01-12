#ifndef _RTC_H
#define _RTC_H

#define TEMP_TIMER_PERIOD 500 

//extern struct repeating_timer temp_timer;
extern volatile bool alarm_fired;

//bool timer_init(int32_t, int32_t);
void rtc_setup();
void print_current_time();

#endif

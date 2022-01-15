#ifndef _TIMER_H
#define _TIMER_H

#define DEBOUNCE_MS 50     

//extern repeating_timer_t t;
//extern volatile bool timer_request;
extern volatile bool alarm_fired;

//bool timer_init(int32_t);
void alarm_init(uint32_t);

#endif

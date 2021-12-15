#ifndef _TIMER_H
#define _TIMER_H

#define TEMP_TIMER_PERIOD 500      
#define LIGHT_TIMER_PERIOD 1000     

extern struct repeating_timer temp_timer;
extern struct repeating_timer light_timer;
extern volatile bool temperature_timer_request;
extern volatile bool light_timer_request;

bool timer_init(int32_t, int32_t);

#endif

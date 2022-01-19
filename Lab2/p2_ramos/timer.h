#ifndef _TIMER_H
#define _TIMER_H    

extern repeating_timer_t timer;
extern volatile bool timer_request;

bool timer_init(int32_t);

#endif

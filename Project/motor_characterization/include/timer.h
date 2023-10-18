#ifndef _TIMER_H
#define _TIMER_H    

#define TIMER_PERIOD_MS     1     // 10 ms

extern repeating_timer_t timer;

bool timer_init(int32_t);

#endif

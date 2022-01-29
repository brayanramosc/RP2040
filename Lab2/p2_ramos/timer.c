#include "pico/stdlib.h"
#include <time.h>

#include "timer.h"
#include "events.h"

repeating_timer_t timer;

bool timer_callback(repeating_timer_t *t){
    EV_TIMER = 1;
    return true;
}

bool timer_init(int32_t period_ms){
    bool timer_is_available = add_repeating_timer_ms(-period_ms, timer_callback, NULL, &timer);

    if(timer_is_available)
    {
        return true;
    }
    return false;
}

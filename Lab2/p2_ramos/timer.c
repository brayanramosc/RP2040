#include "pico/stdlib.h"
#include <stdio.h>
#include <time.h>

#include "timer.h"

repeating_timer_t timer;
volatile bool timer_request = false;

bool timer_callback(repeating_timer_t *t){
    timer_request = true;
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

#include "pico/stdlib.h"

#include "timer.h"

struct repeating_timer temp_timer;
struct repeating_timer light_timer;
volatile bool temperature_timer_request = false;
volatile bool light_timer_request = false;

bool temperature_timer_callback(repeating_timer_t *t){
    temperature_timer_request = true;
    return true;
}

bool light_timer_callback(repeating_timer_t *t){
    light_timer_request = true;
    return true;
}

bool timer_init(int32_t temp_period_ms, int32_t light_period_ms){
    bool temp_timer_is_available = add_repeating_timer_ms(-temp_period_ms, temperature_timer_callback, NULL, &temp_timer);
    bool light_timer_is_available = add_repeating_timer_ms(-light_period_ms, light_timer_callback, NULL, &light_timer);

    if(temp_timer_is_available && light_timer_is_available)
    {
        return true;
    }
    return false;
}

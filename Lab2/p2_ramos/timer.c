#include "pico/stdlib.h"
#include <stdio.h>
#include <time.h>

#include "timer.h"

//repeating_timer_t t;
alarm_id_t alarm_id;
//volatile bool timer_request = false;
volatile bool timer_fired = false;

/*bool timer_callback(repeating_timer_t *t){
    timer_request = true;
    return true;
}*/

int64_t alarm_callback(alarm_id_t alarm_id, void *user_data){
    //printf("Timer %d fired!\n", (int) id);
    timer_fired = true;
    return 0;
}

/*bool timer_init(int32_t period_ms){
    bool timer_is_available = add_repeating_timer_ms(-period_ms, timer_callback, NULL, &temp_timer);

    if(timer_is_available)
    {
        return true;
    }
    return false;
}*/

void alarm_init(uint32_t alarm_ms){
    printf("Evento de tecla\n");
    add_alarm_in_ms(alarm_ms, alarm_callback, NULL, false);
}

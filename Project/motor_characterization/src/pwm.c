#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
//#include "hardware/clocks.h"
//#include "pico/util/datetime.h"
//#include <time.h>
//#include "pico/time.h"
#include "pwm.h"
#include "events.h"

uint pwm_motor_slice_num;
uint pwm_measure_slice_num;
uint pwm_motor_chan;
uint16_t levelValue = 0;
//uint8_t edgeCounter = 0;
uint64_t t1 = 0;
uint64_t t2 = 0;

void callback (uint gpio, uint32_t events) {
    //edgeCounter++;
    EV_EDGE = true;
    t1 = t2;
    t2 = time_us_64();
    /*if (edgeCounter == 1) t1 = time_us_64();
    else {
        edgeCounter = 1;
        t2 = time_us_64();
        printf("Period: %llu\n", t2-t1);
        t1 = t2; t2 = 0;
    }*/
}

float measure_frequency (uint gpio) {
    uint32_t counter;
    uint8_t zeroCount = 2;
    uint32_t delay = 100;

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_RISING);
    pwm_config_set_clkdiv(&cfg, PWM_CLK_DIV);
    pwm_init(pwm_measure_slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    //uint64_t firstTime = to_us_since_boot(get_absolute_time());

    for (int i = 0; i < zeroCount; i++) {
        pwm_set_counter(pwm_measure_slice_num, 0);
        pwm_set_enabled(pwm_measure_slice_num, true);
        sleep_ms(delay);
        pwm_set_enabled(pwm_measure_slice_num, false);
        
        counter = pwm_get_counter(pwm_measure_slice_num);
        if (counter >= 100) break;
        delay *= 10;
    }

    //uint32_t freq = 1000*counter / delay;
    
    printf("Counter: %d, Delay: %d\n", counter, delay);
    //printf("RPMs: %d\n", (uint32_t)((freq * 60) / SLOTS));
    //uint64_t secondTime = to_us_since_boot(get_absolute_time());
    uint64_t t1 = time_us_64();
    sleep_ms(1);
    uint64_t t2 = time_us_64();

    absolute_time_t firstTimestamp = get_absolute_time();
    sleep_ms(1);
    absolute_time_t secondTimestamp = get_absolute_time();

    printf("Diferencia 1: %llu us\n", t2-t1);
    printf("Diferencia 2: %llu us\n", absolute_time_diff_us(firstTimestamp, secondTimestamp));
    return SLOTS;
}

void pwm_setup (void) {
    // Set GPIOs for PWM mode
    gpio_set_function(PWM_GPIO_MOTOR, GPIO_FUNC_PWM);

    // Get slice and channels
    pwm_motor_slice_num = pwm_gpio_to_slice_num(PWM_GPIO_MOTOR);
    pwm_measure_slice_num = pwm_gpio_to_slice_num(PWM_GPIO_MEASURE);
    pwm_motor_chan = pwm_gpio_to_channel(PWM_GPIO_MOTOR);
    
    // Init pin
    gpio_init(PWM_GPIO_MEASURE);
    gpio_set_dir(PWM_GPIO_MEASURE, GPIO_IN);

    // Configure GPIO Interrupt
    gpio_set_irq_enabled_with_callback(PWM_GPIO_MEASURE, GPIO_IRQ_EDGE_RISE, true, &callback);

    // Set frequency and duty
    pwm_set_wrap(pwm_motor_slice_num, PWM_TOP);
    pwm_set_chan_level(pwm_motor_slice_num, pwm_motor_chan, PWM_LEVEL_VALUE);

    // Set the PWM running
    pwm_set_enabled(pwm_motor_slice_num, true);
}

void pwm_change_level(uint16_t level) {
    levelValue = level;
    //printf("Nivel: %d\n", levelValue);
    //printf("Nivel: %d\n", level);
    pwm_set_chan_level(pwm_motor_slice_num, PWM_MOTOR_CH, level);
}

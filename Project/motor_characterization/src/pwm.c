#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pwm.h"

uint pwm_motor_slice_num;
uint pwm_measure_slice_num;
uint pwm_motor_chan;

float measure_frequency (uint gpio) {
    uint16_t counter;

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_RISING);
    pwm_config_set_clkdiv(&cfg, PWM_CLK_DIV);
    pwm_init(pwm_measure_slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    pwm_set_enabled(pwm_measure_slice_num, true);
    sleep_ms(10);
    pwm_set_enabled(pwm_measure_slice_num, false);

    /*for (int i = 0; i < 10; i++) {
        pwm_set_enabled(pwm_measure_slice_num, true);
        sleep_ms(1);
        pwm_set_enabled(pwm_measure_slice_num, false);
        counter = pwm_get_counter(pwm_measure_slice_num);
        printf("Counter: %d\n", counter);
    }*/

    counter = pwm_get_counter(pwm_measure_slice_num);
    float freq = counter / 10.f;

    printf("Slice num: %d\n", pwm_measure_slice_num);
    printf("Counter: %d\n", counter);

    return freq;
}

float measure_duty_cycle(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    //assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    //uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(pwm_measure_slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    pwm_set_enabled(pwm_measure_slice_num, true);
    sleep_ms(10);
    pwm_set_enabled(pwm_measure_slice_num, false);
    float counting_rate = clock_get_hz(clk_sys) / 100;
    float max_possible_count = counting_rate * 0.01;

    return pwm_get_counter(pwm_measure_slice_num) / max_possible_count;
}

void pwm_setup (void) {
    // Set GPIOs for PWM mode
    gpio_set_function(PWM_GPIO_MOTOR, GPIO_FUNC_PWM);

    // Get slice and channels
    pwm_motor_slice_num = pwm_gpio_to_slice_num(PWM_GPIO_MOTOR);
    pwm_measure_slice_num = pwm_gpio_to_slice_num(PWM_GPIO_MEASURE);
    pwm_motor_chan = pwm_gpio_to_channel(PWM_GPIO_MOTOR);

    // Set frequency and duty
    pwm_set_wrap(pwm_motor_slice_num, PWM_TOP);
    pwm_set_chan_level(pwm_motor_slice_num, pwm_motor_chan, PWM_LEVEL_VALUE);

    // Set the PWM running
    pwm_set_enabled(pwm_motor_slice_num, true);
}

void pwm_change_level(uint16_t level) {
    pwm_set_chan_level(pwm_motor_slice_num, PWM_MOTOR_CH, level);
}

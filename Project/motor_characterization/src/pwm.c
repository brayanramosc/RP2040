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
    uint8_t zeroCount = 3;
    uint16_t delay = 10;

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_RISING);
    pwm_config_set_clkdiv(&cfg, PWM_CLK_DIV);
    pwm_init(pwm_measure_slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    for (int i = 0; i < zeroCount; i++) {
        pwm_set_enabled(pwm_measure_slice_num, true);
        sleep_ms(delay);
        pwm_set_enabled(pwm_measure_slice_num, false);

        counter = pwm_get_counter(pwm_measure_slice_num);
        if (counter != 0) break;
        delay *= 10;
    }

    float freq = counter * 100;
    
    printf("Counter: %d\n", counter);
    printf("RPMs: %d\n", (uint32_t)((freq * 60) / SLOTS));

    return freq / SLOTS;
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
    printf("Nivel: %d\n", level);
    pwm_set_chan_level(pwm_motor_slice_num, PWM_MOTOR_CH, level);
}

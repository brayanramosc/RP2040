#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pwm.h"
#include "events.h"

uint pwm_motor_slice_num;
uint pwm_measure_slice_num;
uint pwm_motor_chan;
uint64_t t1 = 0;
uint64_t t2 = 0;

void callback (uint gpio, uint32_t events) {
    EV_EDGE = true;
    t1 = t2;
    t2 = time_us_64();
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
    printf("Level: %d", level);
    pwm_set_chan_level(pwm_motor_slice_num, PWM_MOTOR_CH, level);
}

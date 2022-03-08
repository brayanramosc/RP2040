#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pwm.h"

uint8_t pwm_slice_num;
uint8_t pwm_chan_0;
uint8_t pwm_chan_1;

void pwm_setup (void) {
    // Set GPIOs for PWM mode
    gpio_set_function(PWM_GPIO_MOTOR, GPIO_FUNC_PWM);
    gpio_set_function(PWM_GPIO_LED, GPIO_FUNC_PWM);

    // Get slice and channels
    pwm_slice_num = pwm_gpio_to_slice_num(PWM_GPIO_MOTOR);
    pwm_chan_0 = pwm_gpio_to_channel(PWM_GPIO_MOTOR);
    pwm_chan_1 = pwm_gpio_to_channel(PWM_GPIO_LED);

    // Set frequency and duty
    pwm_set_wrap(pwm_slice_num, PWM_TOP);
    pwm_set_chan_level(pwm_slice_num, pwm_chan_0, PWM_LEVEL_VALUE);
    pwm_set_chan_level(pwm_slice_num, pwm_chan_1, PWM_LEVEL_VALUE);

    // Set the PWM running
    pwm_set_enabled(pwm_slice_num, true);
}

void pwm_change_level(uint chan, uint16_t level) {
    pwm_set_chan_level(pwm_slice_num, chan, level);
}

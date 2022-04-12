#ifndef _PWM_H_
#define _PWM_H_

// GPIO and channel for each output
#define PWM_GPIO_MOTOR      14
#define PWM_MOTOR_CH        0
#define PWM_GPIO_MEASURE    11

#define PWM_CLK_DIV         1.f

#define PWM_FREQ_10KHZ      12500
#define PWM_TOP             PWM_FREQ_10KHZ*2
#define PWM_LEVEL_VALUE     PWM_TOP

// Functions
void pwm_setup (void);
float measure_frequency (uint);
void pwm_change_level(uint16_t);

#endif

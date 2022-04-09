#ifndef _PWM_H_
#define _PWM_H_

// GPIO and channel for each output
#define PWM_GPIO_MOTOR      14
#define PWM_MOTOR_CH        0

#define PWM_FREQ_10KHZ      12500
#define PWM_TOP             PWM_FREQ_10KHZ*2
#define PWM_LEVEL_VALUE     0

// Extern variables
extern uint pwm_chan;

// Functions
void pwm_setup (void);
void pwm_change_level (uint, uint16_t);

#endif

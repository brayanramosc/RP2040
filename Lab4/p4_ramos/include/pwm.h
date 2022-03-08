#ifndef _PWM_H_
#define _PWM_H_

// GPIO for each output
#define PWM_GPIO_MOTOR      14
#define PWM_GPIO_LED        15

#define PWM_TOP             12500   // Freq: 10KHz
#define PWM_LEVEL_VALUE     PWM_TOP/2

// Extern variables
extern uint8_t pwm_chan_0;
extern uint8_t pwm_chan_1;

// Functions
void pwm_setup (void);
void pwm_change_level (uint, uint16_t);

#endif

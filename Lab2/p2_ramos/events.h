#ifndef _EVENTS_H_
#define _EVENTS_H_

typedef union {
    uint8_t reg;
    struct{
        uint8_t flag0 : 1;
        uint8_t flag1 : 1;
        uint8_t flag2 : 1;
        uint8_t flag3 : 1;
        uint8_t flag4 : 1;
        uint8_t flag5 : 1;
        uint8_t flag6 : 1;
        uint8_t flag7 : 1;
    }flags;
}_events_str;

typedef struct {
    uint16_t year   : 12;
    uint8_t month   : 4;
    uint8_t days    : 5;
}date_str;

extern volatile _events_str _events;

#define PENDING_EVENTS  _events.reg
#define EV_TIMER        _events.flags.flag0
#define EV_KBI          _events.flags.flag1 
#define EV_RTC          _events.flags.flag2

#define RUN_MODE DEBUG
#define PRINT_TIME_COUNT    200
#define LED_ON_COUNT        12000
#define CONFIG_MESSAGE      " A para config. "
#define DEBOUNCE_MS 10
#define LED_PIN 15

void events_controller(void);

#endif

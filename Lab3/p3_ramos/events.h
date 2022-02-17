#ifndef _EVENTS_H_
#define _EVENTS_H_

// Event handling struct
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

extern volatile _events_str _events;

// Events definitions
#define PENDING_EVENTS  _events.reg
#define EV_TIMER        _events.flags.flag0
#define EV_KBI          _events.flags.flag1 
#define EV_UART         _events.flags.flag2

// Value for run mode
#define RUN_MODE DEBUG

// Help values
#define CONFIG_MESSAGE      " A para config. "
#define DEBOUNCE_MS         10

// Functions
void events_controller(void);

#endif

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

typedef union {
    float fp;
    uint8_t bytes[4];
}ieee754;

extern volatile _events_str _events;

// Events definitions
#define PENDING_EVENTS  _events.reg
#define EV_TIMER        _events.flags.flag0
#define EV_KBI          _events.flags.flag1 

// Value for run mode
#define RUN_MODE        DEBUG

// Help values
#define OPT1_MESSAGE    "1. Seguimiento"
#define OPT2_MESSAGE    "2. Consulta"
#define MAIN_PERIOD     5
#define DEBOUNCE_MS     10

// Functions
void events_controller(void);

#endif

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
extern          ieee754    	lat, longt;
extern bool     isTimeVisible;
extern bool     saveCoords;

// Events definitions
#define PENDING_EVENTS  _events.reg
#define EV_TIMER        _events.flags.flag0
#define EV_KBI          _events.flags.flag1 
#define EV_UART         _events.flags.flag2

// Value for run mode
#define RUN_MODE        NDEBUG

// Help values
#define OPT1_MESSAGE    "1. Seguimiento"
#define OPT2_MESSAGE    "2. Consulta"
#define SYNC_MESSAGE    "Sincronizando..."
#define TIME_MESSAGE    "Hora: "
#define LAT_MESSAGE     "Lat: "
#define LONG_MESSAGE    "Long: "
#define NO_USB_MESSAGE1 "  No se detecta "
#define NO_USB_MESSAGE2 "     USB...     "
#define MAIN_PERIOD     5
#define DEBOUNCE_MS     10
#define SHOW_DATA_CNT   650 // 3 Seconds
#define TWO_SECONDS_CNT 400 // 2 Seconds

// Functions
void get_coords_from_eeprom(void);
void coords_to_degrees(void);
void events_controller(void);

#endif

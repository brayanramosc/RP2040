#ifndef _UTILS_H
#define _UTILS_H

#define CONFIG_MESSAGE  " A para config. "
#define OPT1_MESSAGE    "1. Config. fecha "
#define OPT2_MESSAGE    "2. Config. alarma"
#define SAVE_MESSAGE    " D para guardar "
#define YEAR_MESSAGE    "Anio: " 
#define MONTH_MESSAGE   "Mes: " 
#define DAY_MESSAGE     "Dia: " 
#define HOUR_MESSAGE    "Hora: "
#define MINUTE_MESSAGE  "Minutos: "
#define SET_TIME_MODE       0
#define SET_ALARM_MODE      1

void print_two_lines(bool, uint8_t *, uint8_t *, uint8_t, uint8_t);
uint8_t digits_counter(uint16_t);
void config_handler(uint8_t *, char *);

#endif

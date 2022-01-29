#ifndef _RTC_H
#define _RTC_H

void rtc_setup(void);
char* get_date_and_time_str(void);
void set_year(uint16_t);
void set_month(uint8_t);
void set_day(uint8_t);
void set_hour(uint8_t);
void set_minute(uint8_t);
void set_year_alarm(uint16_t);
void set_month_alarm(uint8_t);
void set_day_alarm(uint8_t);
void set_hour_alarm(uint8_t);
void set_minute_alarm(uint8_t);

#endif

/*
 * Arduino DS3231 library API wrapper
 */

#include "DS3231.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
DS3231 *mgos_DS3231_create(int I2C_ADDRESS);

void mgos_DS3231_close(DS3231 *rtc);

void mgos_DS3231_setTime(DS3231 *rtc, int seconds, int minutes, int hours24, int dayOfTheWeekDay, int date, bool Century, int month, int twoDigitYear);

void mgos_DS3231_setTimeSeconds(DS3231 *rtc, int seconds);

void mgos_DS3231_setTimeMinutes(DS3231 *rtc, int minutes);

void mgos_DS3231_setTimeHours(DS3231 *rtc, int hours);

void mgos_DS3231_setTimeDayOfTheWeek(DS3231 *rtc, int dayOfTheWeek);

void mgos_DS3231_setTimeDate(DS3231 *rtc, int date);

void mgos_DS3231_setTimeMonth(DS3231 *rtc, int month);

void mgos_DS3231_setTimeYear(DS3231 *rtc, int twoDigitYear);

int mgos_DS3231_getTimeSeconds(DS3231 *rtc);

int mgos_DS3231_getTimeMinutes(DS3231 *rtc);

int mgos_DS3231_getTimeHours(DS3231 *rtc);

bool mgos_DS3231_getTimeHoursIs12HourClock(DS3231 *rtc);

bool mgos_DS3231_getTimeHoursIsPM(DS3231 *rtc);

int mgos_DS3231_getTimeDayOfTheWeek(DS3231 *rtc);

int mgos_DS3231_getTimeDate(DS3231 *rtc);

int mgos_DS3231_getTimeMonth(DS3231 *rtc);

int mgos_DS3231_getTimeYear(DS3231 *rtc);

bool mgos_DS3231_getTimeYearCentury(DS3231 *rtc);	   

#ifdef __cplusplus
}
#endif  /* __cplusplus */

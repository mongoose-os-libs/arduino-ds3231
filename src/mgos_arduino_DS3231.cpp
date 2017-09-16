
#include "mgos_arduino_DS3231.h"



DS3231 *mgos_DS3231_create(int I2C_ADDRESS) {
  return new DS3231(I2C_ADDRESS);
}

void mgos_DS3231_close(DS3231 *rtc) {
  if (rtc != nullptr) {
    delete rtc;
    rtc = nullptr;
  }
}

void mgos_DS3231_setTime(DS3231 *rtc, int seconds, int minutes, int hours24, int dayOfTheWeekDay, int date, bool Century, int month, int twoDigitYear) {
  if (rtc == nullptr) return;
  rtc->setTime(seconds, minutes, hours24, dayOfTheWeekDay, date, Century, month, twoDigitYear);
}

void mgos_DS3231_setTimeSeconds(DS3231 *rtc, int seconds) {
  if (rtc == nullptr) return;
  rtc->setTimeSeconds(seconds);
}

void mgos_DS3231_setTimeMinutes(DS3231 *rtc, int minutes) {
  if (rtc == nullptr) return;
  rtc->setTimeMinutes(minutes);
}

void mgos_DS3231_setTimeHours(DS3231 *rtc, int hours) {
  if (rtc == nullptr) return;
  rtc->setTimeHours(hours);
}

void mgos_DS3231_setTimeDayOfTheWeek(DS3231 *rtc, int dayOfTheWeek) {
  if (rtc == nullptr) return;
  rtc->setTimeDayOfTheWeek(dayOfTheWeek);
}

void mgos_DS3231_setTimeDate(DS3231 *rtc, int date) {
  if (rtc == nullptr) return;
  rtc->setTimeDate(date);
}

void mgos_DS3231_setTimeMonth(DS3231 *rtc, int month) {
  if (rtc == nullptr) return;
  rtc->setTimeMonth(month);
}

void mgos_DS3231_setTimeYear(DS3231 *rtc, int twoDigitYear) {
  if (rtc == nullptr) return;
  rtc->setTimeYear(twoDigitYear);
}

int mgos_DS3231_getTimeSeconds(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeSeconds();
}

int mgos_DS3231_getTimeMinutes(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeMinutes();
}

int mgos_DS3231_getTimeHours(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeHours();
}

bool mgos_DS3231_getTimeHoursIs12HourClock(DS3231 *rtc) {
  if (rtc == nullptr) return false;
  return rtc->getTimeHoursIs12HourClock();
}

bool mgos_DS3231_getTimeHoursIsPM(DS3231 *rtc) {
  if (rtc == nullptr) return false;
  return rtc->getTimeHoursIsPM();
}

int mgos_DS3231_getTimeDayOfTheWeek(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeDayOfTheWeek();
}

int mgos_DS3231_getTimeDate(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeDate();
}

int mgos_DS3231_getTimeMonth(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeMonth();
}

int mgos_DS3231_getTimeYear(DS3231 *rtc) {
  if (rtc == nullptr) return 0;
  return rtc->getTimeYear();
}

bool mgos_DS3231_getTimeYearCentury(DS3231 *rtc) {
  if (rtc == nullptr) return false;
  return rtc->getTimeYearCentury();
}
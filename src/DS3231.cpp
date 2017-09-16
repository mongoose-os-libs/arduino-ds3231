// DS3231 chip library
// Copyright (C) Free Software Foundation, Inc.
// Distributed under the terms of the GPL v3
// http://www.gnu.org/licenses/gpl-3.0.txt

#include "DS3231.h"
#include <Wire.h>
#if defined(ARDUINO_SAM_DUE)
 #define Wire Wire1
#else
 #define Wire Wire
#endif

#define TIMESECOND 0x00
#define TIMEMINUTE 0x01
#define TIMEHOUR 0x02
#define TIMEDAY 0x03
#define TIMEDATE 0x04
#define TIMECENTURYMONTH 0x05
#define TIMEYEAR 0x06
#define A1SECOND 0x07
#define A1MINUTE 0x08
#define A1HOUR 0x09
#define A1DAYDATE 0x0A
#define A2MINUTE 0x0B
#define A2HOUR 0x0C
#define A2DAYDATE 0x0D
#define CONTROL 0x0E
#define CONTROLL_STATUS 0x0F
#define AGINGOFFSET 0x10
#define MSBOFTEMP 0x11
#define LSBOFTEMP 0x12


uint8_t I2C_ADDRESS;

/* bit twiddeling notes...
 *
 * set bit (byte | 0x80)
 * get bit (byte & 0x80)
 * ignore bit (byte & ~0x80
 * flip bit (byte ^ 0x80 
 *
 */

DS3231::DS3231(uint8_t I2C_Address)
{
	I2C_ADDRESS = I2C_Address;
	Wire.begin();
	writeByte(0x0, 0x0);
}

// TODO: Fix up constructors
DS3231::DS3231()
{

}

void DS3231::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours24, uint8_t dayOfTheWeek, uint8_t date, bool Century, uint8_t month, byte twoDigitYear)
{
	prepWrite(TIMESECOND);
	Wire.write(intToBcd(seconds));
	Wire.write(intToBcd(minutes));
	Wire.write(intToBcd(hours24));
	Wire.write(intToBcd(dayOfTheWeek));
	Wire.write(intToBcd(date));
	if (Century)
		Wire.write(intToBcd(month) | 0x80);
	else
		Wire.write(intToBcd(month));
	Wire.write(intToBcd(twoDigitYear));
	Wire.endTransmission();
}

void DS3231::setTime(uint8_t seconds, uint8_t minutes, uint8_t hours12, bool pm, uint8_t dayOfTheWeek, uint8_t date, bool Century, uint8_t month, byte twoDigitYear)
{
	prepWrite(TIMESECOND);
	Wire.write(intToBcd(seconds));
	Wire.write(intToBcd(minutes));
	if (pm)
		Wire.write(intToBcd(hours12) | 0x60);
	else
		Wire.write(intToBcd(hours12) | 0x40);
	Wire.write(intToBcd(dayOfTheWeek));
	Wire.write(intToBcd(date));
	if (Century)
		Wire.write(intToBcd(month) | 0x80);
	else
		Wire.write(intToBcd(month));
	Wire.write(intToBcd(twoDigitYear));
	Wire.endTransmission();
}

// For testing etc... pass a pointer of char[19] 
void DS3231::getRawData(char raw[]) {
  prepRead(0x00, 19);
  for (int i = 0; i < 19; i++)
    raw[i] = Wire.read();
}

void DS3231::setTimeSeconds(uint8_t seconds) {
	prepWrite(TIMESECOND);
	Wire.write(intToBcd(seconds));
	Wire.endTransmission();
}

void DS3231::setTimeMinutes(uint8_t minutes) {
	prepWrite(TIMEMINUTE);
	Wire.write(intToBcd(minutes));
	Wire.endTransmission();
}

void DS3231::setTimeHours(uint8_t hours) {
	prepWrite(TIMEHOUR);
	Wire.write(intToBcd(hours));
	Wire.endTransmission();
}

void DS3231::setTimeHours(uint8_t hours, bool PM) {
	prepWrite(TIMEHOUR);
	Wire.write(PM ? intToBcd(hours) | 0x60 : intToBcd(hours) | 0x40);
	Wire.endTransmission();
}

void DS3231::setTimeDayOfTheWeek(uint8_t dayOfTheWeek) {
	prepWrite(TIMEDAY);
	Wire.write(intToBcd(dayOfTheWeek));
	Wire.endTransmission();
}

void DS3231::setTimeDate(uint8_t date) {
	prepWrite(TIMEDATE);
	Wire.write(intToBcd(date));
	Wire.endTransmission();
}

void DS3231::setTimeMonth(uint8_t month) {
	prepWrite(TIMECENTURYMONTH);
	Wire.write(intToBcd(month));
	Wire.endTransmission();
}

// TODO: Not working
void DS3231::setTimeMonth(uint8_t month, bool century) {
	prepWrite(TIMECENTURYMONTH);
	Wire.write(century ? Wire.write(intToBcd(month) | 0x80) : Wire.write(intToBcd(month)));
	Wire.endTransmission();
}

void DS3231::setTimeYear(uint8_t twoDigitYear) {
	prepWrite(TIMEYEAR);
	Wire.write(intToBcd(twoDigitYear));
	Wire.endTransmission();
}

uint8_t DS3231::getTimeSeconds() {
	prepRead(TIMESECOND, 1);
	return bcdToInt(Wire.read());
}

uint8_t DS3231::getTimeMinutes() {
	prepRead(TIMEMINUTE, 1);
	return bcdToInt(Wire.read());
}

// FIXME: Why do a wire.peek? why not just clear 0x60 wheather it is set or not?
uint8_t DS3231::getTimeHours() {
	prepRead(TIMEHOUR, 1);
	// if 12 hour clock 0x40 bit is set then ignore 12 hour and BAM/PM 0x20 bit before returning
	return Wire.peek() & 0x40 ? bcdToInt(Wire.read() & ~0x60) : bcdToInt(Wire.read());
}

bool DS3231::getTimeHoursIs12HourClock() {
	prepRead(TIMEHOUR, 1);
	return Wire.read() & 0x40;
}

bool DS3231::getTimeHoursIsPM() {
	prepRead(TIMEHOUR, 1);
	// if 12 hour bit 0x40 is set then return 0x20 AM/PM bit, else calculate AM/PM based off 24 hour clock
	return Wire.peek() & 0x40 ? Wire.read() & 0x20 : bcdToInt(Wire.read()) > 12 ? true : false;
}

uint8_t DS3231::getTimeDayOfTheWeek() {
	prepRead(TIMEDAY, 1);
	return bcdToInt(Wire.read());
}

uint8_t DS3231::getTimeDate() {
	prepRead(TIMEDATE, 1);
	return bcdToInt(Wire.read());
}

// FIXME: Why do a wire.peek? why not just clear 0x80 wheather it is set or not?
uint8_t DS3231::getTimeMonth() {
	prepRead(TIMECENTURYMONTH, 1);
	// century bit is tied into month and should be ignored if set.
	return Wire.peek() & 0x80 ? bcdToInt(Wire.read() & ~0x80) : bcdToInt(Wire.read());
}

uint8_t DS3231::getTimeYear() {
	prepRead(TIMEYEAR, 1);
	return bcdToInt(Wire.read());
}

bool DS3231::getTimeYearCentury() {
	prepRead(TIMECENTURYMONTH, 1);
	return Wire.read() & 0x80;
}

// TODO: Address range 07h to 12h

enum alarm1Mask : uint8_t {
  EverySecond = 15,
  Second = 14,
  Minute = 12,
  Hour = 8,
  Date = 0
};

uint8_t DS3231::getAlarm1Seconds() {
  prepRead(A1SECOND, 1);
  return bcdToInt(Wire.read() & ~0x80);
}

uint8_t DS3231::getAlarm1Minutes() {
  prepRead(A1MINUTE, 1);
  return bcdToInt(Wire.read() & ~0x80);
}

uint8_t DS3231::getAlarm1Hours() {
  prepRead(A1HOUR, 1);
  return bcdToInt(Wire.read() & ~0xE0);
}

bool DS3231::getAlarm1HoursIs12HourClock() {
  prepRead(A1HOUR, 1);
  return Wire.read() & 0x40;
}

bool DS3231::getAlarm1HoursIsPM() {
  prepRead(A1HOUR, 1);
  return Wire.peek() & 0x40 ? Wire.read() & 0x20 : bcdToInt(Wire.read() & ~0x80) > 12 ? true : false;
}

uint8_t DS3231::getAlarm1Date() {
  prepRead(A1DAYDATE, 1);
  return bcdToInt(Wire.read() & ~0xC0);
}

uint8_t DS3231::getAlarm1DayOfTheWeek() {
  prepRead(A1DAYDATE, 1);
  return Wire.read() & 0x0F;
}

bool DS3231::getAlarm1IsDate() {
  prepRead(A1DAYDATE, 1);
  return !(Wire.read() & 0x40);
}

uint8_t DS3231::getAlarm1Mask() {
  prepRead(A1SECOND, 4);
  uint8_t mask = 0;
  mask |= (Wire.read() & 0x80) >> 7;
  mask |= (Wire.read() & 0x80) >> 6;
  mask |= (Wire.read() & 0x80) >> 5;
  mask |= (Wire.read() & 0x80) >> 4;
  return mask;
}

void DS3231::setAlarm1Seconds(uint8_t seconds) {
  writeByte(A1SECOND, intToBcd(seconds) | getBit(A1SECOND, 7)); //carry over A1M1 bit
}

void DS3231::setAlarm1Minutes(uint8_t minutes) {
  writeByte(A1MINUTE, intToBcd(minutes) | getBit(A1MINUTE, 7)); //carry over A1M2 bit
}

void DS3231::setAlarm1Hours(uint8_t hours24) {
  writeByte(A1HOUR, intToBcd(hours24) | getBit(A1HOUR, 7)); //carry over A1M3 bit
}

void DS3231::setAlarm1Hours(uint8_t hours12, bool PM) {
  writeByte(A1HOUR, (PM ? intToBcd(hours12) | 0x60 : intToBcd(hours12) | 0x40) | getBit(A1HOUR, 7)); //carry over A1M3
}
  
// return bit @ address
uint8_t DS3231::getBit(uint8_t address, uint8_t bit) {
  return readByte(address) & (1 << bit);
}

// set bit @ address
void DS3231::setBit(uint8_t address, uint8_t bit, bool value) {
  writeByte(address, value ? readByte(address) | (1 << bit) : readByte(address) & ~(1 << bit));
}
  
//TODO: get rid of % it is huge cpu overhead in AVR
// two digit decimal/bcd(Binary Coded Decimal) conversion. 10 is decimal significant figure. 16 is first nibble. 4 is nibble size.
uint8_t DS3231::intToBcd(uint8_t n) {
  return ((n / 10) << 4) + (n % 10);
}

uint8_t DS3231::bcdToInt(uint8_t bcd) {
  return ((bcd >> 4) * 10) + (bcd % 16);
}


uint8_t DS3231::readByte(uint8_t address) {
  //prepRead(address, 1);
  
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(address);
	Wire.endTransmission();
	Wire.requestFrom(I2C_ADDRESS, (uint8_t)1);

  return Wire.read();
}

void DS3231::writeByte(uint8_t address, uint8_t byte) {
  //prepWrite(address);
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(address);
	Wire.write(byte);
	Wire.endTransmission();

}
   
 // was copy pasting this code, made functions for reuse.
void DS3231::prepWrite(uint8_t address) { 
Wire.beginTransmission(I2C_ADDRESS); 
Wire.write(address); 
}
void DS3231::prepRead(uint8_t address, uint8_t bytes) {
	
	//prepWrite(address); 
	Wire.beginTransmission(I2C_ADDRESS); 
	Wire.write(address); 
	Wire.endTransmission(); 
	Wire.requestFrom(I2C_ADDRESS, (uint8_t)bytes); 
	
	}
		

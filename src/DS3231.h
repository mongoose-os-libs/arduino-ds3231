// DS3231 Arduino chip library
// Copyright (C) Free Software Foundation, Inc.
// Distributed under the terms of the GPL v3
// http://www.gnu.org/licenses/gpl-3.0.txt

#ifndef _KUNDARSA_DS3231_H
#define _KUNDARSA_DS3231_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

//#include <Wire.h>

class DS3231
{
public:
	DS3231();
	DS3231(uint8_t I2C_ADDRESS);

	enum daysOfTheWeek : uint8_t {
		Sunday = 1,
		Monday = 2,
		Tuesday = 3,
		Wednesday = 4,
		Thursday = 5,
		Friday = 6,
		Saturday = 7
	};

	// From datasheet
	/*
	the RTC provides seconds, minutes, hours, day, date, month, and
	year information. The date at the end of the month is automatically
	adjusted for months with fewer than 31 days, including corrections for
	leap year. The clock operates in either the 24-hour or 12-hour format
	with an AM/PM indicator
	*/
	void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours24, uint8_t dayOfTheWeekDay, uint8_t date, bool Century, uint8_t month, byte twoDigitYear);
	void setTime(uint8_t seconds, uint8_t minutes, uint8_t hours12, bool pm, uint8_t dayOfTheWeek, uint8_t date, bool Century, uint8_t month, byte twoDigitYear);

	void getRawData(char raw[]); //pass a pointer of char[19] to be filled with BCD data of chip
	
	void setTimeSeconds(uint8_t seconds);	// range 00-59
	void setTimeMinutes(uint8_t minutes);	// range 00-59
	void setTimeHours(uint8_t hours);		// range 00-23. sets clock to 24 hour mode.
	void setTimeHours(uint8_t hours, bool PM);	// range 01-12. sets clock to 12 hour mode. can set AM as false, and PM as true
	void setTimeDayOfTheWeek(uint8_t dayOfTheWeek);	// range 1-7. can use enum daysOfTheWeek, DS3231::Monday
	void setTimeDate(uint8_t date);			// range 01-31
	void setTimeMonth(uint8_t month);		// range 01-12. clears century bit
	void setTimeMonth(uint8_t month, bool century); // range 01-12 + century. altering century bit changes year to 1. true sets century bit, false unsets it
	void setTimeYear(uint8_t twoDigitYear);	// range 00-99

	//RTC
	uint8_t getTimeSeconds();
	uint8_t getTimeMinutes();
	uint8_t getTimeHours();
	   bool getTimeHoursIs12HourClock();
	   bool getTimeHoursIsPM();
	uint8_t getTimeDayOfTheWeek();
	uint8_t getTimeDate();
	uint8_t getTimeMonth();
	uint8_t getTimeYear();
	   bool getTimeYearCentury();		// returns true if the clock 2 digit year rolled over

	//Alarm1
	uint8_t getAlarm1Seconds();
	uint8_t getAlarm1Minutes();
	uint8_t getAlarm1Hours();
	   bool getAlarm1HoursIs12HourClock();
	   bool getAlarm1HoursIsPM();
	uint8_t getAlarm1Date();
	uint8_t getAlarm1DayOfTheWeek();
	   bool getAlarm1IsDate();
	uint8_t getAlarm1Mask();

	void setAlarm1Seconds(uint8_t seconds);
	void setAlarm1Minutes(uint8_t minutes);
	void setAlarm1Hours(uint8_t hours);
	void setAlarm1Hours(uint8_t hours, bool PM);


	uint8_t getBit(uint8_t address, uint8_t bit); //to get the bit 0x0F pass 4 to bit
	void setBit(uint8_t address, uint8_t bit, bool value); //set bit @ address IE: setBit(A1SECONDS, 7, true) will set A1M1

	uint8_t intToBcd(uint8_t n);
	uint8_t bcdToInt(uint8_t bcd);

	uint8_t readByte(uint8_t address); //return 1 byte @ address
	void writeByte(uint8_t address, uint8_t byte); //write byte to address
	
	void prepWrite(uint8_t address);
	void prepRead(uint8_t address, uint8_t bytes);

 private:

};

#endif


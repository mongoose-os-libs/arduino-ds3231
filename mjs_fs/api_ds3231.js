// Arduino DS3231 library API. Source C API is defined at:
// [mgos_arduino_PWMServoDriver.h]


let DS3231 = {
  _create: ffi('void *mgos_DS3231_create(int)'),
  _close: ffi('void mgos_DS3231_close(void *)'),
  _sts: ffi('void mgos_DS3231_setTimeSeconds(void *, int )'),
  _stm: ffi('void mgos_DS3231_setTimeMinutes(void *, int )'),
  _sth: ffi('void mgos_DS3231_setTimeHours(void *, int )'),  
  _stdo: ffi('void mgos_DS3231_setTimeDayOfTheWeek(void *, int )'),
  _std: ffi('void mgos_DS3231_setTimeDate(void *, int )'),
  _stmo: ffi('void mgos_DS3231_setTimeMonth(void *, int )'),
  _sty: ffi('void mgos_DS3231_setTimeYear(void *, int )'),
  _gts: ffi('int mgos_DS3231_getTimeSeconds(void *)'),
  _gtm: ffi('int mgos_DS3231_getTimeMinutes(void *)'),
  _gth: ffi('int mgos_DS3231_getTimeHours(void *)'),
  _gthi: ffi('int mgos_DS3231_getTimeHoursIs12HourClock(void *)'),
  _gthip: ffi('int mgos_DS3231_getTimeHoursIsPM(void *)'),
  _gtdo: ffi('int mgos_DS3231_getTimeDayOfTheWeek(void *)'),
  _gtd: ffi('int mgos_DS3231_getTimeDate(void *)'),
  _gtmo: ffi('int mgos_DS3231_getTimeMonth(void *)'),
  _gty: ffi('int mgos_DS3231_getTimeYear(void *)'),
  _gtyc: ffi('int mgos_DS3231_getTimeYearCentury(void *)'),
  
  _proto: {
    close: function() {
      return DS3231._close(this.rtc);
    },

	setTimeSeconds: function(seconds) {
      return DS3231._sts(this.rtc, seconds);
    },
	
	
	setTimeMinutes: function(minutes) {
      return DS3231._stm(this.rtc, minutes);
    },
	
	setTimeHours: function(hours) {
      return DS3231._sth(this.rtc, hours);
    },	
	
	setTimeDayOfTheWeek: function(dayOfTheWeekDay) {
      return DS3231._stdo(this.rtc, dayOfTheWeekDay);
    },	
	
	setTimeDate: function(date) {
      return DS3231._std(this.rtc, date);
    },	
	
	setTimeMonth: function(month) {
      return DS3231._stmo(this.rtc, month);
    },	
	
	setTimeYear: function(twoDigitYear) {
      return DS3231._sty(this.rtc, twoDigitYear);
    },
	
	getTimeSeconds: function() {
      return DS3231._gts(this.rtc);
    },	
	
	getTimeMinutes: function() {
      return DS3231._gtm(this.rtc);
    },
	
	getTimeHours: function() {
      return DS3231._gth(this.rtc);
    },	
	
	getTimeHoursIs12HourClock: function() {
      return DS3231._gthi(this.rtc);
    },	

	getTimeHoursIsPM: function() {
      return DS3231._gthip(this.rtc);
    },	

	getTimeDayOfTheWeek: function() {
      return DS3231._gtdo(this.rtc);
    },	
	
	getTimeDate: function() {
      return DS3231._gtd(this.rtc);
    },
	
	getTimeMonth: function() {
      return DS3231._gtmo(this.rtc);
    },
	
	getTimeYear: function() {
      return DS3231._gty(this.rtc);
    },
	
	getTimeYearCentury: function() {
      return DS3231._gtyc(this.rtc);
    },
	
  },

  create: function(I2C_ADDRESS) {
    let obj = Object.create(DS3231._proto);
    obj.rtc = DS3231._create(I2C_ADDRESS);
    return obj;
  },

}

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

  // ## **`DS3231.create()`**
  // Create an instance of DS3231 with the methods described below.
  create: function(I2C_ADDRESS) {
    let obj = Object.create(DS3231._proto);
    obj.rtc = DS3231._create(I2C_ADDRESS);
    return obj;
  },

  _proto: {
    // ## **`myds.setVoltage()`**
    // Destroy `myds` instance; it's illegal to call any methods on that instance
    // afterwards.
    // Return value: none.
    close: function() {
      return DS3231._close(this.rtc);
    },

    // ## **`myds.setTimeSeconds(seconds)`**
    // Set seconds, 0 to 59.
    // Return value: none.
    setTimeSeconds: function(seconds) {
      return DS3231._sts(this.rtc, seconds);
    },

    // ## **`myds.setTimeMinutes(minutes)`**
    // Set minutes, 0 to 59.
    // Return value: none.
    setTimeMinutes: function(minutes) {
      return DS3231._stm(this.rtc, minutes);
    },

    // ## **`myds.setTimeHours(hours)`**
    // Set hours, 0 to 23.
    // Return value: none.
    setTimeHours: function(hours) {
      return DS3231._sth(this.rtc, hours);
    },

    // ## **`myds.setTimeDayOfTheWeek(dayOfTheWeekDay)`**
    // Set day of the week, 1 to 7.
    // Return value: none.
    setTimeDayOfTheWeek: function(dayOfTheWeekDay) {
      return DS3231._stdo(this.rtc, dayOfTheWeekDay);
    },

    // ## **`myds.setTimeDate(date)`**
    // Set day of month, 1 to 31.
    // Return value: none.
    setTimeDate: function(date) {
      return DS3231._std(this.rtc, date);
    },

    // ## **`myds.setTimeMonth(month)`**
    // Set month, 1 to 12
    // Return value: none.
    setTimeMonth: function(month) {
      return DS3231._stmo(this.rtc, month);
    },

    // ## **`myds.setTimeYear(twoDigitYear)`**
    // Set two last digits of the year, 0 to 99.
    // Return value: none.
    setTimeYear: function(twoDigitYear) {
      return DS3231._sty(this.rtc, twoDigitYear);
    },

    // ## **`myds.getTimeSeconds()`**
    // Get seconds, 0 to 59.
    getTimeSeconds: function() {
      return DS3231._gts(this.rtc);
    },

    // ## **`myds.getTimeMinutes()`**
    // Get minutes, 0 to 59.
    getTimeMinutes: function() {
      return DS3231._gtm(this.rtc);
    },

    // ## **`myds.getTimeHours()`**
    // Get hours, 0 to 23.
    getTimeHours: function() {
      return DS3231._gth(this.rtc);
    },

    // ## **`myds.getTimeHoursIs12HourClock()`**
    // Return 1 if 12-hour format is used, 0 otherwise.
    getTimeHoursIs12HourClock: function() {
      return DS3231._gthi(this.rtc);
    },

    // ## **`myds.getTimeHoursIsPM()`**
    // Return 1 if it's later than the noon.
    getTimeHoursIsPM: function() {
      return DS3231._gthip(this.rtc);
    },

    // ## **`myds.getTimeDayOfTheWeek()`**
    // Get day of week, 1 to 7.
    getTimeDayOfTheWeek: function() {
      return DS3231._gtdo(this.rtc);
    },

    // ## **`myds.getTimeDate()`**
    // Get day of month, 1 to 31.
    getTimeDate: function() {
      return DS3231._gtd(this.rtc);
    },

    // ## **`myds.getTimeMonth()`**
    // Get month, 1 to 12.
    getTimeMonth: function() {
      return DS3231._gtmo(this.rtc);
    },

    // ## **`myds.getTimeYear()`**
    // Get last two digits of the year, 0 to 99.
    getTimeYear: function() {
      return DS3231._gty(this.rtc);
    },

    // ## **`myds.getTimeYearCentury()`**
    // Return 1 if year is between 2100 and 2199; 0 otherwise.
    getTimeYearCentury: function() {
      return DS3231._gtyc(this.rtc);
    },
  },
}

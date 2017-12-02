Arduino DS3231 High Precision Real Time Clock (RTC) library for Mongoose OS
=========

Tested and works on esp8266/esp32

## Description
DS3231 is a low-cost, extremely accurate I2C real-time clock (RTC), with an integrated temperature-compensated crystal oscillator (TCXO) and crystal. The device incorporates a battery input, disconnect the main power supply and maintains accurate timekeeping. Integrated oscillator improve long-term accuracy of the device and reduces the number of components of the production line.
RTC maintains seconds, minutes, hours, day, date, month, and year information. Less than 31 days of the month, the end date will be automatically adjusted, including corrections for leap year. The clock operates in either the 24 hours or band / AM / PM indication of the 12-hour format. Provides two configurable alarm clock and a calendar can be set to a square wave output. Address and data are transferred serially through an I2C bidirectional bus.See [product page link](https://www.adafruit.com/product/3013) for more information about the hardware.

![alt text](https://cdn-shop.adafruit.com/970x728/3013-02.jpg)

### Features
* Battery
* Operating voltage: 3.3 - 5.5V
* Clock chip: High-precision clock chip DS3231
* Clock Accuracy: 0-40 °C range, the accuracy 2ppm, the error was about 1 minute
* Calendar alarm clock with two
* Programmable square-wave output
* Real time clock generator seconds, minutes, hours, day, date, month and year timing and provide valid until the year 2100 leap year compensation

### Usage

mos.yml, add:
```
config_schema:
 - ["i2c.enable", true]
libs:
 - origin: https://github.com/mongoose-os-libs/arduino-ds3231
 ```
init.js, add:
```
load('api_ds3231.js');
```
[ (JavaScript) usage example](https://github.com/mongoose-os-apps/example-arduino-ds3231-js)

```
#include "mgos_arduino_DS3231.h" 
```

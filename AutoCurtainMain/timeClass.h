// timeClass.h
#ifndef TIMECLASS_H
#define TIMECLASS_H 

// include libraries to be used in source code
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>                       // RTC DS3231 library
#include <Adafruit_LiquidCrystal.h>       // LCD library (for non-I2C connection)
#include "write_lcd.h"

class Time {
  private:
    int _hour;
    int _min;
    int _sec;
    int _period;                          // AM / PM; AM = 0, PM = 1
    String _line1;                         // String displayed on line 1 of LCD during changeTimeMenu() method

  public:
    Time(const String& line1);                                                          // Object constructor    
    String formatTime(int value);                                                       // method to convert hour/min/sec to XX format 
    String formatPeriod(int value);                                                     // method to convert period integer to AM/PM string
    String formatTimeDisplay();                                                         // method using formatTime and formatPeriod to return final LCD line string 
    DateTime changeTimeMenu();                                                          // LCD menu for changing time
    void setTime(DateTime now);                                                         // method to change time attributes via program
    int getHour();                                                                      // returns 24hr scale _hour
    int getMinute();                                                                    // returns _min
};

#endif
// write_lcd.h
#ifndef WRITE_LCD_H
#define WRITE_LCD_H

// include libraries to be used in source code
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>        // RTC DS3231 library
#include <Adafruit_LiquidCrystal.h> // LCD library (for non-I2C connection)

extern Adafruit_LiquidCrystal lcd;

void initLCD(void);
void writeLCD(const String& line_1, const String& line_2);

#endif
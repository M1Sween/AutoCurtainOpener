// write_lcd.h
#ifndef WRITE_LCD_H
#define WRITE_LCD_H

// include libraries to be used in source code
#include <Arduino.h>
//#include <Wire.h>
#include <LiquidCrystal.h> // LCD library (for non-I2C connection)

extern LiquidCrystal lcd;

void initLCD(void);
void writeLCD(const String& line_1, const String& line_2);

#endif
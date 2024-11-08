// write_lcd.h
#ifndef WRITE_LCD_H
#define WRITE_LCD_H

// include libraries to be used in source code
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h> // LCD library (for non-I2C connection)

void initLCD(void);
void writeLCD(const String& line1, const String& line2);

#endif
#include "write_lcd.h"

// Initialize the LCD (RS, E, D4, D5, D6, D7 pins)
Adafruit_LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void initLCD(){
  // Initialize the LCD (16 columns and 2 rows)
  lcd.begin(16, 2);  
}

void writeLCD(const String& line_1, const String& line_2){
  lcd.clear();                    // Clear the LCD screen
  lcd.setCursor(0, 0);            // Set cursor to the top line
  lcd.print(line_1);       // Print the first line
  // delay(100);
  lcd.setCursor(0, 1);            // Move cursor to the second line
  lcd.print(line_2);       // Print the second line
  delay(100);
}
#include "write_lcd.h"

// Initialize the LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void initLCD(){
  // Initialize the LCD (16 columns and 2 rows)
  lcd.begin(16, 2);  
}

void writeLCD(const String& line1, const String& line2){
  lcd.clear();                    // Clear the LCD screen
  lcd.setCursor(0, 0);            // Set cursor to the top line
  lcd.print(line1);       // Print the first line
  lcd.setCursor(0, 1);            // Move cursor to the second line
  lcd.print(line2);       // Print the second line
}
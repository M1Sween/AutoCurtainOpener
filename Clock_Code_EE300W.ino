#include <Wire.h>
#include <RTClib.h>        // RTC DS3231 library
#include <LiquidCrystal.h> // LCD library (for non-I2C connection)

// Create RTC instance
RTC_DS3231 rtc;

// Initialize the LCD (RS, E, D4, D5, D6, D7 pins)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Adjust the pin numbers if different

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the LCD (16 columns and 2 rows)
  lcd.begin(16, 2);
  
  // Initialize the RTC
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC NOT FOUND");
    while (1); // If RTC is not found, halt execution
  }

  // Check if RTC has lost power, if yes set time to compile time
  if (rtc.lostPower()) {
    lcd.setCursor(0, 0);
    lcd.print("Setting Time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to the time this code was compiled
    delay(2000);
  }
}

void loop() {
  // Get current date and time from the RTC
  DateTime now = rtc.now();
  
  // Clear the LCD before updating
  lcd.clear();
  
  // Display Time (HH:MM:SS)
  lcd.setCursor(0, 0);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);
  
  // Display Date (DD/MM/YYYY)
  lcd.setCursor(0, 1);
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);

  // Optional: Print to serial monitor
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  // Delay 1 second before updating the time
  delay(1000);
}


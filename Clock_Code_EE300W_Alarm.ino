#include <Wire.h>
#include <RTClib.h>        // RTC DS3231 library
#include <LiquidCrystal.h> // LCD library (for non-I2C connection)

// Create RTC instance
RTC_DS3231 rtc;

// Initialize the LCD (RS, E, D4, D5, D6, D7 pins)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Alarm time
const int alarmHour = 17;   // Set alarm hour (24-hour format)
const int alarmMinute = 07; // Set alarm minute

// Define the pin for the alarm action (e.g., LED or buzzer)
const int alarmPin = 8; // LED or buzzer connected to pin 8

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD (16 columns and 2 rows)
  lcd.begin(16, 2);
  
  // Initialize the alarm pin
  pinMode(alarmPin, OUTPUT);
  digitalWrite(alarmPin, LOW); // Make sure the alarm pin starts off

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

  // Check if it's time for the alarm
  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    triggerAlarm();  // Execute the alarm action
  } else {
    digitalWrite(alarmPin, LOW); // Make sure alarm is off when not triggered
  }

  // Optional: Print to serial monitor
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  // Delay 1 second before updating the time
  delay(1000);
}

// Function to execute the alarm action
void triggerAlarm() {
  // This function will be called when the alarm time is reached
  digitalWrite(alarmPin, HIGH); // Turn on the alarm (e.g., LED or buzzer)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM!"); // Display the alarm message
  lcd.print(alarmHour);
  lcd.print(":");
  lcd.print(alarmMinute);
  delay(500); // Keep the alarm on for 5 seconds
  digitalWrite(alarmPin, LOW); // Turn off the alarm after 5 seconds
}



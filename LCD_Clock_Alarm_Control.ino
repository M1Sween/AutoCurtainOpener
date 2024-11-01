  #include <Wire.h>
#include <RTClib.h>        // RTC DS3231 library
#include <LiquidCrystal.h> // LCD library (for non-I2C connection)

// Create RTC instance
RTC_DS3231 rtc;

// Initialize the LCD (RS, E, D4, D5, D6, D7 pins)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// default Alarm time
int alarmHour = 24;   // Set alarm hour (24-hour format)
int alarmMinute = 60; // Set alarm minute

// Define the pin for the alarm action (e.g., LED or buzzer)
const int alarmPin = 8; // LED or buzzer connected to pin 8

// Control pins
const int setPin = 9;   // Digital input for set
const int upPin = 10;   // Digital input for up
const int downPin = 11; // Digital input for down

// State variables
bool selectingHours = false;
bool selectingMinutes = false;

// Timing variables
unsigned long lastMillis = 0;
bool flashColon = false;

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

    pinMode(setPin, INPUT_PULLUP);
    pinMode(upPin, INPUT_PULLUP);
    pinMode(downPin, INPUT_PULLUP);
}

void loop() {
    // Get current date and time from the RTC
    DateTime now = rtc.now();
    
    // Read inputs
    static int lastSetState = HIGH;
    int setState = digitalRead(setPin);
    int upState = digitalRead(upPin);
    int downState = digitalRead(downPin);

    // Detect state changes on set button
    if (lastSetState == HIGH && setState == LOW) {
        if (!selectingHours && !selectingMinutes) {
            selectingHours = true; // Start hour selection for alarm
        } else if (selectingHours) {
            selectingHours = false;
            selectingMinutes = true; // Start minute selection for alarm
        } else if (selectingMinutes) {
            selectingMinutes = false; // End minute selection
        }
        delay(200); // Debounce delay
    }
    
    // Adjust hour/minute selection
    if (!selectingHours && upState == LOW) {
        alarmHour = (alarmHour % 23) + 1; // Increase hour, wrap around
        delay(200); // Debounce delay
    } else if (!selectingHours && downState == LOW) {
        alarmHour = (alarmHour == 1) ? 23 : alarmHour - 1; // Decrease hour, wrap around
        delay(200); // Debounce delay
    }

    if (!selectingMinutes && upState == LOW) {
        alarmMinute = (alarmMinute + 1) % 60; // Increase minute, wrap around
        delay(200); // Debounce delay
    } else if (!selectingMinutes && downState == LOW) {
        alarmMinute = (alarmMinute == 0) ? 59 : alarmMinute - 1; // Decrease minute, wrap around
        delay(200); // Debounce delay
    }

    // Flashing colon logic
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= 500) {
        lastMillis = currentMillis;
        flashColon = !flashColon;
    }

    // Update LCD display
    updateDisplay(now);
    
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
    digitalWrite(alarmPin, HIGH); // Turn on the alarm (e.g., LED or buzzer)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALARM!");
    lcd.print(alarmHour);
    lcd.print(":");
    lcd.print(alarmMinute);
    delay(5000); // Keep the alarm on for 5 seconds
    digitalWrite(alarmPin, LOW); // Turn off the alarm after 5 seconds
}

void updateDisplay(DateTime now) {
    lcd.clear();
    
    if (selectingHours) {
        lcd.print("Set Alarm Hour:");
        lcd.setCursor(0, 1);
        lcd.print(alarmHour);

    } else if (selectingMinutes) {
        lcd.print("Set Alarm Min:");
        lcd.setCursor(0, 1);
        lcd.print(alarmMinute);
    } else {
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
        lcd.print(now.year(), DEC);;
    }
}

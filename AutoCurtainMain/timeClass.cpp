// timeClass.cpp
#include "timeClass.h"

Time::Time(const String& line1) {
  // initialize attributes
  _line1 = line1;            // String displayed on line 1 of LCD during changeTime method
  // initialize time object as 12:00:00 AM
  _hour = 12;
  _min = 0;
  _sec = 0;
  _period = 0;    // AM
}

// Format time as two-digit string
String Time::formatTime(int value) {
  if(value < 10) {
    return "0" + String(value);
  } 
  return String(value);
}

// Format period (AM/PM)
String Time::formatPeriod(int value) {
  switch(value){
    case 0:
      return "AM";
      break;
    case 1:
      return "PM";
      break;
  }
}  

// Format full time display
String Time::formatTimeDisplay() {
  String time_str = formatTime(_hour) + ":" +    // XX:XX AM or XX:XX PM
                    formatTime(_min) + " "  +
                    formatPeriod(_period);
  return time_str;
}

// Change time menu
DateTime Time::changeTimeMenu() {
  delay(100);     // include delay so one set button press is not double counted
  // initialize menu variables
  int up, down, set = 0;
  // initialize menu text
  writeLCD(_line1, formatTimeDisplay());

  // changing hour
  while(set != 1){ 
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);

    if(up) {                 // if up button is pressed
      if(_hour == 12) {
        _hour = 1;           // increment hour to 01:XX
      }
      else {
        _hour++;             // increment hour 
      }
      writeLCD(_line1, formatTimeDisplay()); // update display
    }
    else if(down) {         // if down button is pressed
      if(_hour == 1) {
        _hour = 12;         // decrement hour to 12:XX
        }
      else {
        _hour--;            // decrement hour
      } 
      writeLCD(_line1, formatTimeDisplay()); // update display
     }
  }

  delay(100);     // include delay so one set button press is not double counted
  up, down, set = 0;

  // changing minute
  while(set != 1){ 
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);

    if(up) {                 // if up button is pressed
      if(_min == 59) {
        _min = 0;           // increment min to XX:00
      }
      else {
        _min++;             // increment min 
      }
      writeLCD(_line1, formatTimeDisplay()); // update display
    }
    else if(down) {         // if down button is pressed
      if(_min == 0) {
        _min = 59;         // decrement min to XX:59
        }
      else {
        _min--;            // decrement min
      } 
      writeLCD(_line1, formatTimeDisplay()); // update display
     }
  }  

  delay(100);     // include delay so one set button press is not double counted
  up, down, set = 0;

  while(set != 1){ // changing period
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);

    if(up||down) {
      _period = abs(_period - 1);
      writeLCD(_line1, formatTimeDisplay()); // update display
    }
  }

  // return new time in DateTime format (convert 12 hour scale to 24 hour scale)
  int DateTime_hour;
  if(_hour == 12) {
    DateTime_hour = 0 + _period*12;
  }
  else {
    DateTime_hour = _hour + _period*12;
  }
  _sec = 0;
  // rtc.adjust(DateTime(2024, 11, 19, 14, 30, 0)); // YYYY, MM, DD, HH, MM, SS
  return DateTime(2024, 11, 19, DateTime_hour, _min, _sec);    // Set second to 00 because menu does not allow sec to be changed
}

// Set time attributes from DateTime
void Time::setTime(DateTime now) {
  if (now.hour() >= 12) {        // Adjust for PM scale
    _hour = now.hour() - 12;
    _period = 1;               // PM
  } 
  else {
    _hour = now.hour();
    _period = 0;               // AM
  }

  _min = now.minute();
  _sec = now.second();
}

// Return hour in 0-23hr format
int Time::getHour() {
  int DateTime_hour;
  if(_hour == 12) {
    DateTime_hour = 0 + _period*12;
  }
  else {
    DateTime_hour = _hour + _period*12;
  }
  return DateTime_hour;
}

// Return minute
int Time::getMinute() {
  return _min;
}









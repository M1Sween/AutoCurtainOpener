// AutoCurtainMain.ino
// #include "state_transition.h" // state_transition currently unfinished
#include "motor_drive.h"
#include "write_lcd.h"
#include "timeClass.h"
#include <Servo.h>
#include <Wire.h>
#include <RTClib.h>                     // RTC DS3231 library

// initialize globals
String line1;                           // Arduino has its own class for string, std::string does not work
String line2;

Time open_time("Set Open:       ");
Time close_time("Set Close:      ");
Time clock_time("Set Clock:      ");
RTC_DS3231 rtc;                         // (A4 -> SDA, A5 -> SCL)

// NOTE: setup is run once automatically when the arduino is pwrd on or code deployed; no need to call it anywhere
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // intialize motor_drive and write_lcd source code
  initMotor();
  initLCD();
  // initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.setCursor(0, 0);
    lcd.print("RTC NOT FOUND");
    while (1); // Halt execution if the RTC is not detected
  }
  // write computer time to RTC
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  // rtc.adjust(DateTime(2024, 11, 19, 14, 30, 0)); // YYYY, MM, DD, HH, MM, SS 
}


void menu(){
  // initialize menu text
  line1 = "Set open/close <";     // 0 case
  line2 = "Set time        ";     // 1 case
  writeLCD(line1, line2);

  delay(250);                     // avoid double counting set button

  // initialize menu variables
  int menu_cursor = 0;
  int up, down, set = 0;

  while(set != 1){
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);

    if(up||down){                 // if either cursor button is pressed
      switch(menu_cursor){
        case 0:                   // if top line currently selected
          if(down){               // if down arrow is pressed
            menu_cursor = 1;      // move cursor to bottom line
            line1 = "Set open/close  ";    // 0 case
            line2 = "Set time       <" ;   // 1 case
          }
          break;
        case 1:                   // if bottom line currently selected
          if(up){                 // if up button pressed 
            menu_cursor = 0;      // move cursor to top line
            line1 = "Set open/close <";    // 0 case
            line2 = "Set time        " ;   // 1 case
          }
        break;    
      }
      writeLCD(line1, line2);
    }
  delay(100); 
  }
  if(set){
      switch(menu_cursor){
        case 0:
          submenu0();             // Change open/close schedule menu
          break;
        case 1:
          submenu1();             // Change clock time LCD menu
          break;
      }
    }
}

// Change open/close schedule menu
void submenu0(){
  // initialize menu text
  line1 = "Set open/close <";     // 0 case
  line2 = "Set time        ";     // 1 case
  writeLCD(line1, line2);

  delay(250);                     // avoid double counting set button

  // initialize menu variables
  int menu_cursor = 0;
  int up, down, set = 0;

  while(set != 1){
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);
    if(up||down){                 // if either cursor button is pressed
      switch(menu_cursor){
        case 0:                   // if top line currently selected
          if(down){               // if down arrow is pressed
            menu_cursor = 1;      // move cursor to bottom line
            line1 = "Set open time   ";     // 0 case
            line2 = "Set close time <";     // 1 case
          }
          break;
        case 1:                   // if bottom line currently selected
          if(up){                 // if up button pressed 
            menu_cursor = 0;      // move cursor to top line
            line1 = "Set open time  <";     // 0 case
            line2 = "Set close time  ";     // 1 case
          }
        break;    
      }
      writeLCD(line1, line2);
    }
  delay(100);   
  }
  if(set){
      switch(menu_cursor){
        case 0:
          open_time.changeTimeMenu();           // launch menu to set new open time
          break;
        case 1:
          close_time.changeTimeMenu();          // launch menu to set new close time
          break;
      }
    }
}

// Change clock time LCD menu
void submenu1() {                 
  // Get RTC current date and time
  DateTime now = rtc.now();

  // Update clock_time object to display when menu is launched
  clock_time.setTime(now);

  // Launch LCD menu to change clock_time, store new DateTime created in menu
  DateTime new_RTC_time = clock_time.changeTimeMenu();

  // Write new clock time to RTC
  rtc.adjust(new_RTC_time); 
}

void loop() {
  // put your main code here, to run repeatedly:

  // define variable for drive direction as enum type used in motor_drive.cpp function
  DIRECTION direction;

  // read digital inputs from remote transmitter
  int up = digitalRead(10);
  int down = digitalRead(11);
  int set = digitalRead(12);

  // update clock_time
  clock_time.setTime(rtc.now());

  // check if clock time is at open or close time; open/close accordingly (limit switches to be added)
  if(clock_time.getHour() == open_time.getHour() && clock_time.getMinute() == open_time.getMinute() && clock_time.getSecond() < 1) {
    drive(OPEN);
    delay(2000);
    drive(STOP);
  }
  else if(clock_time.getHour() == close_time.getHour() && clock_time.getMinute() == close_time.getMinute() && clock_time.getSecond() < 1) {
    drive(CLOSE);
    delay(2000);
    drive(STOP);
  }

  // if no inputs received, display the time 
  if(up == 0 && down == 0 && set == 0) {
    writeLCD(clock_time.formatTimeDisplay(),"                ");
  }
  else {
    // launch programming menu if set button is pressed
    if(set) {
      menu();       
    }

    // open/close curtains if up/down button is pressed (limit switches to be added)
    while(up || down) {  
      // read digital inputs from remote transmitter
      up = digitalRead(10);
      down = digitalRead(11);
      if(up){
        direction = OPEN;
        line1 = "Opening...      ";
        line2 = "                ";
      }
      else if(down){
        direction = CLOSE;
        line1 = "Closing...      ";
        line2 = "                ";
      }
      writeLCD(line1, line2);
      drive(direction);
    }
    drive(STOP);
  }

  delay(100);
}

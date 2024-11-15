// AutoCurtainMain.ino
// #include "state_transition.h" // state_transition currently unfinished
#include "motor_drive.h"
#include "write_lcd.h"
#include <Servo.h>

// NOTE: setup is run once automatically when the arduino is pwrd on or code deployed; no need to call it anywhere
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  // intialize motor_drive source code
  initMotor();
}

String line1;
String line2;

void menu(){
  delay(500);
  // initialize menue variable
  int menu_cursor = 0;
  int up;
  int down;
  int set = 0;
  // initialize menue text
  line1 = "Set open/close <";    // 0 case
  line2 = "Set time        ";    // 1 case
  writeLCD(line1, line2);
  

  while(set != 1){
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);
    delay(500);
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
  }
  if(set){
      switch(menu_cursor){
        case 0:
          submenu0();
          break;
        case 1:
          //submenu1();
          break;
      }
    }
}

void submenu0(){
  delay(500);
  // initialize menue variables
  int menu_cursor = 0;
  int up;
  int down;
  int set = 0;
  // initialize menue text 
  line1 = "Set open time   <";    // 0 case
  line2 = "Set close time   ";    // 1 case
  writeLCD(line1, line2);
  

  while(set != 1){
    // read digital inputs from remote transmitter
    up = digitalRead(10);
    down = digitalRead(11);
    set = digitalRead(12);
    delay(500);
    if(up||down){                 // if either cursor button is pressed
      switch(menu_cursor){
        case 0:                   // if top line currently selected
          if(down){               // if down arrow is pressed
            menu_cursor = 1;      // move cursor to bottom line
            line1 = "Set open time    ";    // 0 case
            line2 = "Set close time  <";   // 1 case
          }
          break;
        case 1:                   // if bottom line currently selected
          if(up){                 // if up button pressed 
            menu_cursor = 0;      // move cursor to top line
            line1 = "Set open time   <";    // 0 case
            line2 = "Set close time   ";   // 1 case
          }
        break;    
      }
      writeLCD(line1, line2);
    } 
  }
  if(set){
      switch(menu_cursor){
        case 0:
          //submenu0_0();
          break;
        case 1:
          //submenu0_1();
          break;
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  //String line1;
  //String line2;

  // read digital inputs from remote transmitter
  int up = digitalRead(10);
  int down = digitalRead(11);
  int set = digitalRead(12);

  
  if(set){
    menu();
  }

  // define variable for drive direction as enum type used in motor_drive.cpp function
  DIRECTION direction;

  // assign drive direction according to remote button inputs
  if(up){
    direction = OPEN;
    line1 = "Opening...";
    line2 = "line 2";
  }
  else if(down){
    direction = CLOSE;
    line1 = "Closing...";
    line2 = "line 2";
  }
  else{
    direction = STOP;
    line1 = "Idle";
    line2 = "line 2";
  }

  delay(200);
  drive(direction);
  writeLCD(line1, line2);
  
}

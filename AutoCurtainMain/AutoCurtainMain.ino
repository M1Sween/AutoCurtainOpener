// AutoCurtainMain.ino
// #include "state_transition.h" // state_transition currently unfinished
#include "motor_drive.h"
#include "write_lcd.h"
#include <Servo.h>

// NOTE: setup is run once automatically when the arduino is pwrd on or code deployed; no need to call it anywhere
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // intialize motor_drive source code
  initMotor();
}

String line1;
String line2;

void loop() {
  // put your main code here, to run repeatedly:
  //String line1;
  //String line2;

  // read digital inputs from remote transmitter
  int up = digitalRead(10);
  int down = digitalRead(11);
  int set = digitalRead(12);

  // define variable for drive direction as enum type used in motor_drive.cpp function
  DIRECTION direction;

  // assign drive direction according to remote button inputs
  if(up){
    direction = OPEN;
    line1 = " Opening...";
    line2 = " ";
  }
  else if(down){
    direction = CLOSE;
    line1 = " Closing...";
    line2 = " ";
  }
  else{
    direction = STOP;
    line1 = " Idle";
    line2 = " ";
  }

  delay(200);
  drive(direction);
  writeLCD(line1, line2);
  
}

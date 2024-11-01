// AutoCurtainMain.ino
// #include "state_transition.h" // state_transition currently unfinished
#include "motor_drive.h"
#include <Servo.h>

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // intialize motor_drive source code
  initMotor();

  // read digital inputs from remote transmitter
  int up = digitalRead(10);
  int down = digitalRead(11);
  int set = digitalRead(12);

  // define variable for drive direction as enum type used in motor_drive.cpp function
  DIRECTION direction;

  // assign drive direction according to remote inputs
  if(up){
    direction = OPEN;
  }
  else if(down){
    direction = CLOSE;
  }
  else{
    direction = STOP;
  }

  drive(direction);
}

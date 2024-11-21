// motor_drive.cpp
#include "motor_drive.h"

// DEFINE SERVO OBJECT TO BE USED IN GLOBAL SPACE
Servo ESC;                  // initialize instance of Servo class

// INITIALIZATION FOR PWM OUTPUT TO ESC
void initMotor() {
  int PWM1_pin = 9;         // Use D9 PWM pin
  int min_PW = 1000;        // minimum pulse width 2ms [units in us]
  int max_PW = 2000;        // max pulse width
  ESC.attach(PWM1_pin, min_PW, max_PW);  // Attach the ESC to the specified pin and pulse widths
}
  

// Function to drive motor in specified direction
void drive(DIRECTION drive_direction){
  int speed;                // max CCW = 0, max CW = 1023, idle = 511

  // set analog value to turn into PWN according to input cmd
  switch (drive_direction) {
    case STOP:            //  stop motor drive
      speed = 511;
      break;
    case OPEN:            // drive motor in CCW direction at quarter speed
      speed = 383;
      break;
    case CLOSE:           // drive motor in CW direction at quarter speed
      speed = 639;
      break;
    default:
      speed = 511;
      break;
  // END OF CASE STRUCTURE
  } 

  // change duty cycle scale
  speed = map(speed, 0, 1023, 0, 180);
  // drive motor / send PWM to ESC (write to pin 9)
  ESC.write(speed);
}



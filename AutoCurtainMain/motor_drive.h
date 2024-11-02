// motor_drive.h
#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

#include <Arduino.h>
#include <Servo.h>

// DEFINE STATE ENUM
enum DIRECTION {STOP, OPEN, CLOSE};

// Declare the Servo object as extern; tells the compiler that ESC is defined elsewhere, allowing it to be used in the .ino file without needing to redefine it. 
extern Servo ESC; // Declaration only, no definition


// Declare the function that transitions between states
void initMotor(void);
void drive(DIRECTION drive_direction);

#endif
// motor_drive.h
#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

#include <Arduino.h>
#include <Servo.h>

// DEFINE STATE ENUM
enum DIRECTION {STOP, OPEN, CLOSE};



// Declare the function that transitions between states
void initMotor(void);
void drive(DIRECTION drive_direction);

#endif
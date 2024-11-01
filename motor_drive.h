// motor_drive.h
#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

// DEFINE STATE ENUM
enum DIRECTION {STOP, OPEN, CLOSE};

// Declare the function that transitions between states
void drive(DIRECTION drive_direction);

#endif
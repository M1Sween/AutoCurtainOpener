#include <Servo.h>

Servo ESC;

int Speed;



void setup() {
  int PWM1_pin = 9;         // Use D9 PWM pin
  int min_PW = 1000;        // minimum pulse width 2ms [units in us]
  int max_PW = 2000;        // max pulse width
  ESC.attach(PWM1_pin, min_PW, max_PW); // 
}

void loop() {
  Speed = analogRead(A0);                // ranges 0 - 1023
  Speed = map(Speed, 0, 1023, 0, 180);  // Change duty cycle scale
  ESC.write(Speed);                     // Send PWM to ESC (write pin 9)
}
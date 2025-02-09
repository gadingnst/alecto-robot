#ifndef ROBOT_H
#define ROBOT_H

#include <ESP32Servo.h>

/**
 * All servos are connected to the 5V and GND pins
 * VIN -> 5V -> red wire
 * GND -> GND -> orange wire
 */
#define SERVO_FOOT_LEFT_PIN  17
#define SERVO_FOOT_RIGHT_PIN 21
#define SERVO_LEG_LEFT_PIN   18
#define SERVO_LEG_RIGHT_PIN  41

class Robot {
public:
  Robot();
  void setup();
  void walkForward();
  void moonwalk();

private:
  Servo footLeft;
  Servo footRight;
  Servo legLeft;
  Servo legRight;

  int footLeftPin;
  int footRightPin;
  int legLeftPin;
  int legRightPin;

  void moveSmooth(Servo &servo, int startAngle, int endAngle, int delayMs);
};

#endif
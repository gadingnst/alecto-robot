// Robot.h
#ifndef ROBOT_H
#define ROBOT_H

#include <ESP32Servo.h>

class Robot {
public:
  Robot(int footLeftPin, int footRightPin, int legLeftPin, int legRightPin);
  void begin();
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
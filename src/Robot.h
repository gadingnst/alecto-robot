#ifndef ROBOT_H
#define ROBOT_H

#include <ESP32Servo.h>

/**
 * All servos are connected to the 5V and GND pins
 * VIN -> 5V -> red wire
 * GND -> GND -> brown wire
 * PWM -> GPIO -> orange wire
 */
#define SERVO_FOOT_LEFT_PIN  6
#define SERVO_FOOT_RIGHT_PIN 7
#define SERVO_LEG_LEFT_PIN   17
#define SERVO_LEG_RIGHT_PIN  16

class Robot {
public:
  Robot();
  void setup();
  void walkForward();
  void walkBackward();
  void moonwalk();
  void turnLeft();
  void turnRight();
  void stop();

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
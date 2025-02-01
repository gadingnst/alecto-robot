#ifndef ROBOT_H
#define ROBOT_H

#include <ESP32Servo.h>

#define SERVO_FOOT_LEFT_PIN  17  // Adjust these pin numbers
#define SERVO_FOOT_RIGHT_PIN 21  // according to your setup
#define SERVO_LEG_LEFT_PIN   18
#define SERVO_LEG_RIGHT_PIN  41

class Robot {
public:
  Robot();
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
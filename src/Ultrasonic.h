#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

/**
 * Ultrasonic sensor
 * VCC -> 5V -> blue wire
 * GND -> GND -> orange wire
 * TRIG -> GPIO -> green wire
 * ECHO -> GPIO -> yellow wire
 */
#define TRIG_PIN 4  // GPIO pin for TRIG
#define ECHO_PIN 5  // GPIO pin for ECHO

class Ultrasonic {
public:
  Ultrasonic(int trigPin = TRIG_PIN, int echoPin = ECHO_PIN);
  void setup();
  long measureDistance();
  bool isObjectClose(long thresholdDistance);

private:
  int trigPin;
  int echoPin;
};

#endif // ULTRASONIC_H 
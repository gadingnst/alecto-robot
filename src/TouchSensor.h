#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

#define TOUCH_PIN 5

class TouchSensor {
public:
  TouchSensor();
  void setup();
  bool isTouched();

private:
  int touchPin;
  int touchState;
};

#endif
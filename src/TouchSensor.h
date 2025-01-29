#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

class TouchSensor {
public:
  TouchSensor(int pin);
  void setup();
  bool isTouched();

private:
  int touchPin;
  int touchState;
};

#endif
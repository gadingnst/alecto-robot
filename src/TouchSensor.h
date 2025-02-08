#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

#define DEFAULT_TOUCH_PIN 5

class TouchSensor {
public:
  TouchSensor();
  void setup(int pin = DEFAULT_TOUCH_PIN);
  bool isTouched();

private:
  int touchPin;
  int touchState;
};

#endif
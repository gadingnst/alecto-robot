#include "TouchSensor.h"

TouchSensor::TouchSensor() {}

void TouchSensor::setup(int pin) {
  touchPin = pin;
  pinMode(touchPin, INPUT);
  Serial.println("Touch Sensor initialized");
}

bool TouchSensor::isTouched() {
  touchState = digitalRead(touchPin);
  return touchState == HIGH;
}
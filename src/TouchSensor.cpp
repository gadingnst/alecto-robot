#include "TouchSensor.h"

TouchSensor::TouchSensor() {
  touchPin = TOUCH_PIN;
}

void TouchSensor::setup() {
  pinMode(touchPin, INPUT);
  Serial.println("Touch Sensor initialized!");
}

bool TouchSensor::isTouched() {
  touchState = digitalRead(touchPin);
  return touchState == HIGH;
}
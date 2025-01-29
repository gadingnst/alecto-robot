#include "TouchSensor.h"

TouchSensor::TouchSensor(int pin) {
  touchPin = pin;
}

void TouchSensor::setup() {
  pinMode(touchPin, INPUT);
  Serial.println("Touch Sensor initialized!");
}

bool TouchSensor::isTouched() {
  touchState = digitalRead(touchPin);
  return touchState == HIGH;
}
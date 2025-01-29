#include <Arduino.h>
#include "TouchSensor.h"
#include "Robot.h"

// pins according to ESP32-S3 pinout
const int footLeftPin = 17;
const int footRightPin = 21;
const int legLeftPin = 18;
const int legRightPin = 41;

// pins according to ESP32-S3 pinout
TouchSensor touchSensor(4);
Robot robot(footLeftPin, footRightPin, legLeftPin, legRightPin);

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring ESP32-S3...");
  touchSensor.setup();
  robot.begin();
}

void loop() {
  if (touchSensor.isTouched()) {
    Serial.println("Touch sensor is touched!");
    Serial.println("Walking forward...");
    robot.walkForward();
  }
  delay(1000);
}

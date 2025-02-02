#include <Arduino.h>
#include "TouchSensor.h"
#include "Audio.h"

TouchSensor touchSensor;
Audio* audio;

void setup() {
  Serial.begin(115200);
  touchSensor.setup();
  audio = new Audio(ICS43434);
}

void loop() {
  if (touchSensor.isTouched()) {
    Serial.println("\r\nRecord start!\r\n");
    audio->Record();
    Serial.println("Recording Completed.");
    delete audio;
  }
}

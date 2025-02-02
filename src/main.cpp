#include <Arduino.h>
#include "TouchSensor.h"
#include "Audio.h"
#include "SDCard.h"

TouchSensor touchSensor;
SDCard sdCard;


void setup() {
  Serial.begin(115200);
  touchSensor.setup();
  
  if (!sdCard.begin()) {
    Serial.println("SD Card initialization failed!");
    return;
  }
}

void loop() {
  if (touchSensor.isTouched()) {
    Serial.println("\r\nRecord start!\r\n");
    Audio* audio = new Audio(ICS43434);
    audio->Record();
    Serial.println("Recording Completed.");
    delete audio;
  }
}

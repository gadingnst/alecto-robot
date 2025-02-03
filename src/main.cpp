#include <Arduino.h>
#include "TouchSensor.h"
#include "Audio.h"

TouchSensor touchSensor;
Audio* audio;
SDCard *sdCard;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  audio = new Audio(sdCard);
}

void loop() {
  if (touchSensor.isTouched()) {
    // sdCard->begin();
    // Serial.println("\r\nRecord start!\r\n");
    // audio->Record("/recording-4.wav");
    // delete audio;
    // sdCard->end();
    // Serial.println("Recording Completed.");
    Serial.println("Hello ESP-32");
  }
  delay(1000);
}

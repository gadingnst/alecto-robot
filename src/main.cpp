#include <Arduino.h>
#include "TouchSensor.h"
#include "Audio.h"
#include "Speaker.h"

TouchSensor touchSensor;
Audio* audio;
SDCard *sdCard;
Speaker speaker;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  audio = new Audio(sdCard, ICS43434);
  speaker.setup(sdCard);
}

void loop() {
  if (touchSensor.isTouched()) {
    // Serial.println("\r\nRecord start!\r\n");
    // audio->Record();
    // Serial.println("Recording Completed.");
    // delete audio;

    // speaker.playMP3File("/short-audio-10.mp3");
    // Serial.println("Audio playback completed");

    Serial.println("Hello ESP-32");
  }
  delay(1000);
}

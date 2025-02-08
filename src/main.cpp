#include <Arduino.h>
#include "TouchSensor.h"
#include "Audio.h"

TouchSensor touchSensor;
Audio* audio;
SDCard* sdCard;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  audio = new Audio(sdCard);
  Serial.println("Setup complete.");
}

void loop() {
  if (touchSensor.isTouched()) {
    if (!audio->isRecording) {
      Serial.println("\r\nRecording started!\r\n");
      audio->StartRecording("/recording-8.wav", 10000);
    } else {
      audio->StopRecording();
      Serial.println("Recording stopped.");
      audio->Reset();
    }
    delay(500);
  }

  if (audio->isRecording) {
    audio->ProcessRecording();
  }
}

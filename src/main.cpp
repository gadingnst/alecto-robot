#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"

TouchSensor touchSensor;
AudioRecorder* recorder;
SDCard* sdCard;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  recorder = new AudioRecorder(sdCard);
  Serial.println("Setup complete.");
}

void loop() {
  if (touchSensor.isTouched()) {
    recorder->Record("/recording-10.wav");
  }
  recorder->HandleRecording();
}

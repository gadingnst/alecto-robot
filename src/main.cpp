#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"

SDCard* sdCard;
TouchSensor touchSensor;
AudioRecorder recorder;
AudioPlayer player;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  recorder.setup(sdCard);
  player.setup(sdCard);
  Serial.println("Setup complete.");
}

void loop() {
  if (touchSensor.isTouched()) {
    recorder.record("/recording-10.wav");
  }
  recorder.handleRecording();
}
